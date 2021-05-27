 $fn = 20;
    
    flight_radius = 17.5; // 1.75cm
    shaft_radius = 5; // 4 mm
    dart_length = 150; // 15 cm
    flight_depth = 2; // 2 mm
    padding = 10; // 1 cm
    back_padding = 25; // 2.5 cm
    device_length = 230; // 23 cm
    
    elastic_radius = 2.5; // 2.5mm
    sled_width = 20;
    sled_height = 10;
    sled_padding = (2 * elastic_radius) + 8;
    sled_depth = (flight_radius * 2) + (sled_padding * 2);

module sled() {  
    // Sled on the top of the barrel
    translate([0,0,sled_height])
    rotate([0, 180, 0])
    difference() {
        union() {
            cube([sled_width, sled_depth, sled_height]);
            translate([0, sled_depth/2, 0])
            rotate([0, 90, 0])
            cylinder(r = shaft_radius, h = sled_width);
        }
        
        translate([sled_width, elastic_radius + 4, 0])
        cylinder(r = elastic_radius, h = sled_width);
        
        translate([sled_width, sled_depth - elastic_radius - 4, 0])
        cylinder(r = elastic_radius, h = sled_width);
    }
}

module barrel() {
    difference() {
        union() {
            // Dart barrel
            cube([device_length + back_padding, flight_radius * 2, flight_radius + padding]);
            
            // Sled on the front of the barrel for holding the elastic band
            translate([sled_height, -sled_padding, flight_radius + padding + sled_height])
            rotate([0, 180, 0])
            difference() {
                translate([-sled_height, 0, 0])
                cube([sled_height * 2, sled_depth, flight_radius + padding + sled_height]);
        
                translate([sled_height, elastic_radius + 4, 0])
                    cylinder(r = elastic_radius, h = flight_radius + padding + sled_height);
        
                translate([sled_height, sled_depth - elastic_radius - 4, 0])
                    cylinder(r = elastic_radius, h = flight_radius + padding + sled_height);
                
                translate([-sled_width, sled_padding, 0])
                    cube([sled_width * 2, flight_radius * 2, sled_width]);
            }
            
            // Guard on the back
            translate([device_length, 0, flight_radius + padding])
                cube([back_padding, flight_radius * 2, sled_width]);
        }
        
        // Shaft cutout
        rotate([0, 90, 0])
        translate([-flight_radius - padding, flight_radius, 0])
            cylinder(r = shaft_radius, h = device_length);
        
        
        // Flight cutout
        translate([0,flight_radius - (flight_depth / 2), padding])
            cube([device_length, flight_depth, flight_radius + 1 ]);
    }
}

barrel();

translate([90, 80, 0])
rotate([0, 0, 90])
sled();