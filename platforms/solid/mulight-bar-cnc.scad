// midi-led-bar.scad

depth = 10; // z
height = 15; // y
width = 827.567; // x
width_60 = 814 ;

step= width_60 / 60; // 13.567

rotate([180,0,0])
{
    difference(){
        translate([0,0,0])  cube([width,height,depth]);
        translate([-5,1,1]) cube([width+10 ,height-2,depth-2 ]);

        for ( off =[9 : step: width_60 ] )
        {
            translate([ off,-10,-2])  cube([9,50,4]);
        }
    }
}
