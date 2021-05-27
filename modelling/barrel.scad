$fn = 20;

/*
 * These values are measured for our darts set etc
 */
electromagnet_radius = 20 + 1; // 2 cm + 1 mm
electromagnet_height = 27; // 2.7 cm
elastic_radius = 2.5; // 2.5 mm
flight_radius = 17.5 + 2; // 1.75 cm + 2 mm
shaft_radius = 4 + 1; // 4 mm + 1 mm
dart_length = 150; // 15 cm
flight_depth = 2; // 2 mm

padding = 10; // 1 cm
back_padding = electromagnet_height + 5;
device_length = 200; // 20 cm

sled_width = flight_radius; // Equal to the flight radius.
sled_height = 10; // 1 cm
sled_padding = (2 * elastic_radius) + 8; // Space between for structural integrity
sled_depth = (flight_radius * 2) + (sled_padding * 2);
sled_cutout_radius = shaft_radius - .5; // Subtract a bit from the structure so we can actually slide.

pin_depth = 5; // 5 mm

roof_height = 5;

module sled() {
    // Sled on the top of the barrel
    translate([0, 0, sled_height])
        rotate([0, 180, 0])
            difference() {
                union() {
                    cube([sled_width, sled_depth, flight_radius]);
                    translate([0, sled_depth / 2, 0])
                        rotate([0, 90, 0])
                            cylinder(r = sled_cutout_radius, h = sled_width);
                }

                //TODO: We need to cut out a cross where the dart rests.
                // might be easier to just use a saw :-)

                translate([sled_width, elastic_radius + 4, 0])
                    cylinder(r = elastic_radius, h = sled_width);

                translate([sled_width, sled_depth - elastic_radius - 4, 0])
                    cylinder(r = elastic_radius, h = sled_width);
            }
}

module roof() {
    difference() {
        union() {
            cube([device_length + electromagnet_height, flight_radius * 2, roof_height]);

            translate([device_length,-sled_padding, 0])
                cube([back_padding, sled_depth, flight_radius + padding / 2]);

            translate([0, -sled_padding, 0])
                cube([sled_height * 2, sled_depth, roof_height]);
        }

        translate([device_length, 0, roof_height / 2])
            electromagnet();
    }
}

module barrel() {
    difference() {
        union() {
            // Dart barrel
            cube([device_length, flight_radius * 2, flight_radius + padding]);

            // Sled on the front of the barrel for holding the elastic band
            translate([sled_height, - sled_padding, flight_radius + padding + sled_width])
                rotate([0, 180, 0])
                    difference() {
                        // Pillar cube
                        translate([- sled_height, 0, 0])
                            cube([sled_height * 2, sled_depth, flight_radius + padding + sled_width]);

                        // Gap between pillars
                        translate([- sled_height, sled_padding, 0])
                            cube([sled_height * 2, flight_radius * 2, sled_width]);

                        // Right cutout
                        translate([sled_height, elastic_radius + 4, 0])
                            cylinder(r = elastic_radius, h = flight_radius + padding + sled_width);

                        // Top right cutout
                        translate([- sled_height, elastic_radius + 4, 0])
                            rotate([0, 90, 0])
                                cylinder(r = elastic_radius, h = sled_width);

                        // Left cutout
                        translate([sled_height, sled_depth - elastic_radius - 4, 0])
                            cylinder(r = elastic_radius, h = flight_radius + padding + sled_width);

                        // Top left cutout
                        translate([- sled_height, sled_depth - elastic_radius - 4, 0])
                            rotate([0, 90, 0])
                                cylinder(r = elastic_radius, h = sled_width);
                    }

            translate([device_length, - sled_padding, 0])
                difference() {
                    // Guard on the back
                    cube([back_padding, sled_depth, padding + flight_radius]);

                    // Electromagnet cutout
                    rotate([0, 90, 0])
                        translate([- padding - flight_radius, sled_padding + flight_radius, 0])
                            cylinder(r = electromagnet_radius, h = electromagnet_height);

                    // Left pin
                    translate([back_padding / 2, sled_padding / 2, padding + flight_radius - pin_depth])
                        cylinder(r = elastic_radius, h = pin_depth);

                    // Right pin
                    translate([back_padding / 2,
                                sled_padding + flight_radius * 2 + sled_padding / 2,
                                padding + flight_radius - pin_depth])
                        cylinder(r = elastic_radius, h = pin_depth);
                }
        }

        // Shaft cutout
        rotate([0, 90, 0])
            translate([- flight_radius - padding, flight_radius, 0])
                cylinder(r = shaft_radius, h = device_length);

        // Flight cutout
        translate([0, flight_radius - (flight_depth / 2), padding])
            cube([device_length, flight_depth, flight_radius + 1]);
    }
}

module electromagnet() {
    translate([0, electromagnet_radius, electromagnet_radius])
        rotate([0, 90, 0])
            cylinder(r = electromagnet_radius, h = electromagnet_height);
}

//barrel();

roof();

translate([90, 80, 9.5])
    rotate([0, 0, 90])
        sled();