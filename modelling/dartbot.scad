use <barrel.scad>;
use <vertical_aim.scad>;
use <gear.scad>;


//color("yellow")
barrel();

translate([30, -13, 39.5])
color("blue")
    rotate([0, 180, 0])
        sled();

translate([0, 39, 19.5 * 2 + 10 + 5])
rotate([180, 0, 0])
//color("red")
roof();


color("purple")
translate([200, -1.5, 10])
electromagnet();