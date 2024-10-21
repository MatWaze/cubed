cub="./cub3D"
dir="maps/invalid/*/*"

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
