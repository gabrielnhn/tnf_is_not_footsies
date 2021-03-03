BITMAP * images[ 10 ];
int current_image = 0;
while ( ... ){
   draw_sprite( image[ current_image ], screeen, ... );
   if ( key[ KEY_RIGHT ] ){
     // cycle to the next image
     current_image = (current_image + 1 ) % 10;
   }
}
