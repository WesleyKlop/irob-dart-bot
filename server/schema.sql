CREATE TABLE calibration (
	calibration_id INTEGER PRIMARY KEY,
	table_height INTEGER NOT NULL,
	created_on DATETIME DEFAULT CURRENT_TIMESTAMP NOT NULL
);

CREATE TABLE calibration_steps (
	calbiration_steps_id INTEGER PRIMARY KEY,
	calibration_id INTEGER NOT NULL,
	step_dir TEXT NOT NULL,
	step_size INTEGER NOT NULL,
	FOREIGN KEY (calibration_id)
      REFERENCES calibration (calibration_id)
         ON DELETE CASCADE
         ON UPDATE NO ACTION

);

