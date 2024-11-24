# cub3D

A Wolfenstein 3D like game, using the miniLibx a simple X-Window (X11R6) programming API in C, designed for students


![screenshot of the game](https://raw.githubusercontent.com/Louisa4124/Cub3d/master/misc/screenshot0.png)


## Installation


```bash
  git clone git@github.com:Louisa4124/Cub3d.git && cd Cub3d && make
```

For bonus part libxfixes-dev is required
```bash
  sudo apt-get install libxfixes-dev -y
  make bonus
```

    
## Features

Mandatory 
- Different texture based on wall orientation
- POV (Point Of View) deplacement with WASD key
- POV z-rotation with ← and →
- Parsing of .cub map
- Color of floor and ceilling


Bonus 
- True 3D engine (also implemented in mandatory)
- Collision with wall (also implemented in mandatory)
- Jump and walk effect
- Floor texture
- POV x-rotation with ↑ and ↓
- All smooth POV rotation with mouse
- Animated sprites in game
- Darkness
- Blur
- Doors
- Menus
- Multithreading


## How it's made ?

#### 3D engine


#### Multithreading

At program start we create a thread pool, and a job queue.
For each task needing parallelism, we can use the job queue, by creating job, pushing them to queue and then signal the semaphore.
For example each frame is sliced in several (16 by default) area and a job is created with the area and the render function to apply.
Thread start waiting on a semaphore, when semaphore is signaled, thread acquire the next job and apply the job's function to the job's data.


## Demo




## Authors

- [@Louisa4124](https://www.github.com/Louisa4124)
- [@titi-rex](https://www.github.com/titi-rex)


## Credits
- grass from 256x256 pixel textures pack 2 by FlakDeau on itch.io
- barricades from isometric props and tents by rubberduck on https://opengameart.org/


## License

[GPLv3](https://www.gnu.org/licenses/gpl-3.0.html)

