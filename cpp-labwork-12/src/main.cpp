#include <iostream>
#include <string>
#include <variant>

#include <lib/database.h>
// I need to be able to parse certain things like Parameters( shit in here )

// FROM
// WHERE
// (LEFT|RIGHT|INNER)JOIN
// CREATE TABLE
// AND
// OR
// IS
// NOT
// NULL
// ON
// UPDATE
// INSERT
// VALUES
// DELETE
// PRIMARY KEY
// FOREIGN KEY

int main() {

  mdb::Database database;

  database.create("people").add("job_id").add("name").add_records({
      {"job_id", 0},
      {"job_id", 1},
      {"job_id", 2},
      {"job_id", 3},
      {"job_id", 4},
      {"job_id", 5},
  }).add_records({
      {"name", "Mike"},
      {"name", "John"},
      {"name", "Doe"},
      {"name", "Dasha"},
      {"name", "Vanya"},
      {"name", "Pasha"},
  });

  // database.create("jobs").add("job_id").add("job").add_records({
  //     {"job_id", 0},
  //     {"job_id", 1},
  //     {"job_id", 2},
  //     {"job_id", 3},
  //     {"job_id", 4},
  //     {"job_id", 6},
  // }).add_records({
  //     {"job", "programmer"},
  //     {"job", "janitor"},
  //     {"job", "dancer"},
  //     {"job", "model"},
  //     {"job", "screenwriter"},
  //     {"job", "hippie"}
  // });

  database.query("select * from people").Display();


  // database.query("SELECT * FROM people WHERE people.name = 'josh'").Display();

}