cub="./cub3D"
dir="/Users/mamazari/Desktop/42-cursus/cub3d/maps/invalid/*/*"

for subdir in $dir;
    do
        for map in $subdir;
            do
                echo $map
                echo
                echo
                $cub $map
                echo "------------------------------------------------------------"
            done
    done