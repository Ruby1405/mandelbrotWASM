# Image documentation of the process

Starting resolution: 1200 by 1200
Starting max iteration: 1000 (I think)
Escape clause at this time was the iteration number at the point when the set repeats itself.
Colouring was determined by a linear map of escape iteration, 0, max iteration, 0 and 360 and then placed as the hue value in hsv with a modulus of black where max iteration was reached.
1. First render
![mandelbrot](01.png)
2. Max 2000 iterations
![mandelbrot](02.png)
3. Max 100 iterations
![mandelbrot](03.png)
4. Escape clause was added for also escaping when `x*x + y*y > 2*2`
![mandelbrot](04.png)
5. Modulus for max generations was removed
![mandelbrot](05.png)
6. Max 200 iterations
![mandelbrot](06.png)
7. Max 500 iterations
![mandelbrot](07.png)
8. Max 1000 iterations
![mandelbrot](08.png)
9. Optimisation: `if(newX == x && newY == y) break;` Modulus black colouring was also reintroduced
![mandelbrot](09.png)
10. Max 100 iterations
![mandelbrot](10.png)
11. Zoomed in on the edge of the set
![mandelbrot](11.png)
12. Max 500 iterations and zoomed in more
![mandelbrot](12.png)
13. Zoomed in MORE
![mandelbrot](13.png)
14. Resolution: 1024 by 1024
Switched to cyclical colouring
![mandelbrot](14.png)
15. Zoomed in more
![mandelbrot](15.png)
16. Attempted optimisation of escape time algorithm
![mandelbrot](16.png)
17. Tweaking
![mandelbrot](17.png)
18. Tweaking
![mandelbrot](18.png)