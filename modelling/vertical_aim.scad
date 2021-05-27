module vertical_aim(radius = 10, space_between = 20, guard_width = 5) {
    difference() {
        total_width = space_between + (guard_width * 2);
        rotate([270, 0, 0])
            cylinder(r = radius, h = total_width);
        
        translate([-radius, 0, -radius])
            cube([radius*2, total_width, radius], center = false);
        
        rotate([270, 0, 0])
        translate([0, 0, guard_width])
            cylinder(r = radius, h = space_between);
    }
}

vertical_aim(30, 45, 12);