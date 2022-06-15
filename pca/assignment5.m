band1 = imread('band1.gif','gif');
band2 = imread('band2.gif','gif');
band3 = imread('band3.gif','gif');
band4 = imread('band4.gif','gif');

[components component1 component2 component3 component4] = principle_component(band1,band2,band3,band4);

imshow(round(component4),[0,255])
pause;
imshow(round(component3),[0,255])
pause;
imshow(round(component2),[0,255])
pause;
imshow(round(component1),[0,255])
