void draw_line(int x1,int y1,int x2,int y2,int nColor)
{
int i,deltax,deltay,numpixels,d,dinc1,dinc2,x,xinc1,xinc2,y,yinc1,yinc2;
//calculate delta-x ,delta-y for initialization
if(x2-x1<0)
{
   deltax=x1-x2;
}
else
{
   deltax=x2-x1;
}
if(y2-y1<0)
{
   deltay=y1-y2;
}
else
{
   deltay=y2-y1;
}
   //initialize all vars based on which is the independent variable
if(deltax>=deltay)
{
   //x is independent variable
   numpixels=deltax+1;
   d=(2*deltay)-deltax;
   dinc1=deltay<<1;
   dinc2=(deltay-deltax)<<1;
   xinc1=1;
   xinc2=1;
   yinc1=0;
   yinc2=1;
}
else
{
   //y is independent variable
   numpixels=deltay+1;
   d=(2*deltax)-deltay;
   dinc1=deltax<<1;
   dinc2=(deltax-deltay)<<1;
   xinc1=0;
   xinc2=1;
   yinc1=1;
   yinc2=1;
}
//make sure x and y mobe in the right directions
if(x1>x2)
{
   xinc1=-xinc1;
   xinc2=-xinc2;
}
if(y1>y2)
{
   yinc1=-yinc1;
   yinc2=-yinc2;
}

//start drawing at <x1,y1>
x=x1;
y=y1;

//draw the pixels

for(i=1;i<numpixels;i++)
{
   //draw pixel
   draw_pixel(x,y,nColor);
   if(d<0)
   {
    d=d+dinc1;
    x=x+xinc1;
    y=y+yinc1;
   }
   else
   {
    d=d+dinc2;
    x=x+xinc2;
    y=y+yinc2;
   }
}
}
