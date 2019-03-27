1) Padding size: 266x266
   Upper-left index: (N/2, N/2)
   Lower-right index: (266-(N/2), 266-(N/2)
2) Raw, If we use this kernel the image will
be too bright.
   0.7788  |  0.8825  |  0.7788
   0.8825  |     1    |  0.8825
   0.7788  |  0.8825  |  0.7788
Normal
   0.1019  |  0.1154  |  0.1019
   0.1154  |  0.1308  |  0.1154
   0.1019  |  0.1154  |  0.1019

Experimantation
1) If you hold N constant and vary sigma, 
the image seems to vary very little in
bluriness, and after a certain point, it
stops becoming more blurry, no matter the 
size of sigma. If you vary N and hold
sigma constant, the blur becomes much more
prominent across the whole image as 
N increases.


2) It appears to highlight edges in images and 
render things that are not edges very dark 
(black).

3) We do not recover the original because the
unsharp mask filter uses the gaussian filter to 
grasp onto sharper, more detailed parts of an 
image and blur them. If you have an already 
blurry image and try to sharpen it, there aren't 
any sharp edges (values) for it to grasp onto,
therefore the "unsharp masked" image that is 
returned is not the original, unblury image. 



Express in mathematical terms how the number of 
calculations your program does grows with the size, 
N, of the kernel.
It grows at a rate of O(N^2). Since, the number of
of calculations is dependent on the kernel size & 
for example, as N were to increase from 3 to 5, 
the number of cells increases from 3x3(9) to 5x5(25).
Ths size can be written in terms of N as NxN or N^2..
