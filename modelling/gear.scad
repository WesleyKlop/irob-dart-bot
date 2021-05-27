// Achim Breidenbach achim@boinx.com
// based on the work form https://www.thingiverse.com/thing:54395

// ----------- Parameters to enter:

// Gear height:
height = 2.5;					

// Size of the Shaft hole. (zero for no hole)
hole_diameter = 4;  				

// Number of Cogs:
z = 30;

// module (make sure that all gears of your trasmit has the same module)
// https://en.wikipedia.org/wiki/Gear#Standard_pitches_and_the_module_system
m = 1.5;


// ----------- Calculations:

d = z * m;
da = d + 2 * m;
c = 0.167 * m;
df = d - 2*(m + c);

//Size of the internal donut.
internal_diameter = df; 			

//Resolution of the donut.
res = 100;		//[1:100]

//Number of Cogs.
cogs=z;			

//Total length of the cog. 
cog_length= (da - df)/2;		

//Width of the cogs base. 
cog_base_width=((df * 3.14159 ) / z)/2;	

//Height of the cogs base. 
cog_base_height=height; 

//Width of the tip.
cog_tip_width=cog_base_width*0.5;    

//Height of the tip.
tip_height=height*0.9;	 

//Amount of the cog length, which lacks angle, aka height of the cogbase.
no_angle = (da-d)/2; 


module cog(){

	union(){									
		difference(){										

			translate ([0,0,0]){
				cylinder(height,internal_diameter/2,internal_diameter/2, $fn = res, center=true) ;
			}

			translate ([0,0,0]){
				cylinder(height+2,hole_diameter/2,hole_diameter/2, $fn = res, center=true);

			}
		}
	}


	for ( i = [0 : (cogs-1)] ){			//the spikes
		hull(){
    		rotate( i * 360 / cogs, [0, 0, 1])
    			translate([internal_diameter/2,0,0]){
    				cube ([no_angle*2,cog_base_width,cog_base_height],center=true);
						translate([cog_length-0.5,0,0]) {
							cube ([.1,cog_tip_width,tip_height],center=true);		
						}
				}


		}
	}
}


translate([0,0,height/2]){
	color([0,0.6,0.8]){
		cog(); 
	}
}

