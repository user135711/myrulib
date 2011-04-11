<?php

require_once '../Common/datafile.php';
require_once '../Common/genres.php';
require_once '../Common/strutils.php';

function utf($string)
{
  return iconv("WINDOWS-1251", "UTF-8", $string); 
}

function letter($string)
{
	$char_list = 'А Б В Г Д Е Ж З И Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ы Э Ю Я A B C D E F G H I J K L M N O P Q R S T U V W X Y Z';
	$letter = utf8_substr($string,0,1);
	$letter = strtoupperEx($letter,0,1);
	if (strpos($char_list, $letter) === false) { $letter = "#"; };
	return $letter; 
}

function convert_auth($sqlite_db, $min)
{
  $sqlite_db->query("begin transaction;");

  $sqlite_db->query("DELETE FROM authors");

  $handle = fopen("author", "r");
  while (!feof($handle)) {
	$buffer = fgets($handle, 4096);
	if(empty($buffer{0})) continue;
	$fields = explode(chr(9), $buffer);
	$id = $fields[0];
	$names = explode(",", $fields[1]); 
	$last_name = utf(trim($names[0]));
	$first_name = utf(trim($names[1]));
	$middle_name = utf(trim($fields[2]));
	$full_name = trim(trim($last_name." ".$first_name)." ".$middle_name);
	$letter = letter($full_name);
	$numb = $fields[5];
	echo "Auth: ".$letter." - ".$id." - ".$full_name."\n";
	$sql = "INSERT INTO authors (id, number, letter, full_name, first_name, middle_name, last_name) VALUES(?,?,?,?,?,?,?)";
	$insert = $sqlite_db->prepare($sql);
	$insert->execute(array($id, $numb, $letter, $full_name, $first_name, $middle_name, $last_name));
  }
  fclose($handle);
  $sqlite_db->query("commit;");
}  

function convert_genr($sqlite_db, $min)
{
  $sqlite_db->query("begin transaction;");
  $sqlite_db->query("DELETE FROM genres");

  $handle = fopen("booktags", "r");
  while (!feof($handle)) {
	$buffer = fgets($handle, 4096);
	if(empty($buffer{0})) continue;
	$fields = explode(chr(9), $buffer);
	$book = $fields[0];
	$genre = GenreCode($fields[1]);
	if (!empty($genre{0})) {
		echo "Genr: ".$book." - ".$fields[1]."\n";
		$sql = "INSERT INTO genres(id_book, id_genre) VALUES(?,?)";
		$insert = $sqlite_db->prepare($sql);
		$err = $insert->execute(array($book, $genre));
	}
  }
  fclose($handle);
  $sqlite_db->query("commit;");
}

function convert_seqn($sqlite_db, $min)
{
  $sqlite_db->query("begin transaction;");
  $sqlite_db->query("DELETE FROM sequences");

  $handle = fopen("series", "r");
  while (!feof($handle)) {
	$buffer = fgets($handle, 4096);
	if(empty($buffer{0})) continue;
	$fields = explode(chr(9), $buffer);
	$code = $fields[0];
	$name = utf(trim($fields[1]));
	echo "Seqn: ".$code." - ".$name."\n";
	$sql = "INSERT INTO sequences (id, value) VALUES(?,?)";
	$insert = $sqlite_db->prepare($sql);
	$insert->execute(array($code, $name));
  }
  fclose($handle);
  $sqlite_db->query("commit;");
}

function convert_book($sqlite_db, $min)
{
  $sqlite_db->query("begin transaction;");
  $sqlite_db->query("DELETE FROM books");

  $handle = fopen("book", "r");
  while (!feof($handle)) {
	$buffer = fgets($handle, 4096);
	if(empty($buffer{0})) continue;
	$fields = explode(chr(9), $buffer);
	$book  = $fields[0];
	$auth  = $fields[1];
	$title = utf(trim($fields[2]));
	$lang  = utf(trim($fields[3]));
	$seqn  = $fields[4];
	$numb  = $fields[5];
	$year  = $fields[6];
	$file  = utf(trim(str_replace("\\","/",$fields[8]))).utf(trim($fields[9]));
	$type  = substr(strrchr($file, '.'), 1);
	$size  = $fields[10];
	$date  = $fields[12];
	$crc32 = $fields[13];
	
	echo "Book: ".$book." - ".$type." - ".$title."\n";

	$sql = "INSERT INTO books (id, id_author, title, file_name, file_size, file_type, genres, created, lang, year, md5sum) VALUES(?,?,?,?,?,?,?,?,?,?,?)";
	$insert = $sqlite_db->prepare($sql);
	$insert->execute(array($book, $auth, $title, $file, $size, $type, NULL, $date, $lang, $year, $crc32));

	if ($seqn != 0) {
		$sql = "INSERT INTO bookseq(id_book, id_seq, number) VALUES(?,?,?)";
		$insert = $sqlite_db->prepare($sql);
		$insert->execute(array($book, $seqn, $numb));
	}
  }
  fclose($handle);
}  

function convert_info($sqlite_db, $min)
{
  $sqlite_db->query("begin transaction;");

  $handle = fopen("bookanno", "r");
  while (!feof($handle)) {
	$buffer = fgets($handle, 4096);
	if(empty($buffer{0})) continue;
	$fields = explode(chr(9), $buffer);
	$code = $fields[0];
	$text = utf(trim($fields[1]));
	$sql = "UPDATE books SET description=? where id=?";
	$insert = $sqlite_db->prepare($sql);
	$insert->execute(array($text, $code));
  }
  fclose($handle);
  $sqlite_db->query("commit;");
}

function convert_dates($mysql_db, $sqlite_db, $min)
{
  $sqlite_db->query("begin transaction;");

  $sqlite_db->query("DELETE FROM dates");

  $sqltest = "
    SELECT DATE_FORMAT(Time,'%y%m%d') as Time, MAX(BookId) as Max, MIN(BookId) as Min, COUNT(BookId) AS Num
    FROM libbook 
	WHERE Deleted<>1 AND libbook.BookId>$min
	GROUP BY DATE_FORMAT(libbook.Time,'%y%m%d')
  ";

  $query = $mysql_db->query($sqltest);
  while ($row = $query->fetch_array()) {
	echo "Date: ".$row['Time']." - ".$row['Max']." - ".$row['Min']."\n";
    $sql = "INSERT INTO dates (id, lib_max, lib_min, lib_num) VALUES(?,?,?,?)";
    $insert = $sqlite_db->prepare($sql);
    if($insert === false){ $err= $dbh->errorInfo(); die($err[2]); }
    $err= $insert->execute(array($row['Time'], $row['Max'], $row['Min'], $row['Num']));
    if($err === false){ $err= $dbh->errorInfo(); die($err[2]); }
    $insert->closeCursor();
  }
  $sqlite_db->query("commit;");
}  

function setup_params($sqlite_db, $date, $type)
{
  $sqlite_db->query("begin transaction;");
  
  $sqlite_db->query("DELETE FROM params;");
  $sqlite_db->query("INSERT INTO params(id,text)  VALUES (1,  'Flibusta library');");
  $sqlite_db->query("INSERT INTO params(id,value) VALUES (2,  1);");
  $sqlite_db->query("INSERT INTO params(id,text)  VALUES (3,  'TRAUM');");
  $sqlite_db->query("INSERT INTO params(id,text)  VALUES (11, 'traumlibrary.net');");
  $sqlite_db->query("INSERT INTO params(id,value) VALUES (20, $date);");
  $sqlite_db->query("INSERT INTO params(id,text)  VALUES (21, '$type');");
  
  $sqlite_db->query("commit;");
}

function FullImport($file, $date)
{
  $sqlite_db = new PDO('sqlite:./'.$file);
  
  create_tables($sqlite_db);
  setup_params($sqlite_db, $date, "FULL");
  
  convert_auth($sqlite_db, 0);
  convert_seqn($sqlite_db, 0);
  convert_genr($sqlite_db, 0);
  convert_book($sqlite_db, 0);

/*
  convert_sequences($mysql_db, $sqlite_db, 0);
  convert_dates($mysql_db, $sqlite_db, 0);
  
  convert_zips($mysql_db, $sqlite_db, 0);
  convert_files($mysql_db, $sqlite_db, 0, 0);
*/
  create_indexes($sqlite_db);
  convert_info($sqlite_db, 0);
}

$sqlitefile = 'myrulib.db';

$date = date('Ymd');
echo "Today: ".$date."\n";
include('settings.php');
system("rm $sqlitefile");
$sqlite_db = new PDO('sqlite:'.$sqlitefile);
FullImport($sqlitefile, $date);
system("zip traumlib.db.zip $sqlitefile");

?>