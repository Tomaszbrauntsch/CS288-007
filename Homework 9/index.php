<html>
<head>
<style type="text/css">
table, th, td{
border: 1px solid black;
}
table{
border-collapse: collapse; width:50%;
}
th,td{
padding:0.3em;
}
</style>
<script>
function sortTable(n) {
  var table, rows, switching, i, x, y, shouldSwitch, dir, switchcount = 0;
  table = document.getElementById("myTable");
  switching = true;
  // Set the sorting direction to ascending:
  dir = "asc";
  while (switching) {
    switching = false;
    rows = table.rows;
    /* Loop through all table rows (except the
    first, which contains table headers): */
    for (i = 1; i < (rows.length - 1); i++) {
      shouldSwitch = false;
      /* Get two elements to compare */
      x = rows[i].getElementsByTagName("td")[n];
      y = rows[i + 1].getElementsByTagName("td")[n];
      // if(parseFloat(x) != NaN){
      if (dir == "asc") {
        if (parseInt(x.innerHTML.toLowerCase(),10) > parseInt(y.innerHTML.toLowerCase(), 10)){ // X greater than y
          shouldSwitch = true;
          break;
        }
      } else if (dir == "desc") {
        if (parseInt(x.innerHTML.toLowerCase(),10) < parseInt(y.innerHTML.toLowerCase(), 10)) { // y is greater than x
          shouldSwitch = true;
          break;
        }
      }
    //}
  }
    if (shouldSwitch) {
      rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
      switching = true;
      switchcount ++;
    } else {
      if (switchcount == 0 && dir == "asc") {
        dir = "desc";
        switching = true;
      }
    }
  }
}
</script>
</head>
<body>
<?php
/*
Created By: Tomasz Brauntsch
CS-288 007
Professor Ding
December 21, 2023
*/
echo "<head><style>table, th, td{border: 1px solid black;} table{border-collapse: collapse; width:50%;}</style></head>";
        $mysqli = new mysqli("localhost", "lamp", "lamp", "cshwstock");
        if ($mysqli->connect_errno){
                die("Failed to connect to MYSQL");
        }
 
        $sql = "SELECT * FROM site_data"; 
        $stmt = $mysqli->prepare($sql);
        $stmt->execute();
        $result = $stmt->get_result();
        $index = 1;
        echo "<table id='myTable'><tr><th onclick='sortTable(0)'>Index</th><th onclick='sortTable(1)'>Symbol</a></th><th onclick='sortTable(2)'>Name</th><th onclick='sortTable(3)'>Price</th><th onclick='sortTable(4)'>Change</th><th onclick='sortTable(5)'>Volume</th></tr>";
        if(!$mysqli->query($sql)){
                die("error ($mysqli->errno) $mysqli-<error<br> SQL = $sql\n");
        }
        while($row = $result->fetch_assoc()){
                echo "<tr><td>$index</td><td>$row[stock_symbol]</td><td>$row[stock_name]</td><td>$row[stock_price]</td><td>$row[stock_change]</td><td>$row[stock_volume]</td></tr>";
                $index++;
        }
 
        echo "</table>";
        $stmt->close();
?>
</table>
</body>
</html>