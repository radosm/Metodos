%I=imread("64x64/blond.pgm");
I=imread("128x128/einstein.pgm");
J=imnoise(im2double(I),'gaussian',0,0.01);
%J=imnoise(im2double(I),'salt & pepper');
J=im2uint8(J);
imshow(J);
