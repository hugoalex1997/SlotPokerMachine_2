#!/usr/bin/env bash

function show_help_message {
    echo "
	        Usage: $0 [options]     
                         
                -b|--build		- Build Project (-f if cache remove is desired)
                -g, --game		- Run Binary Application
                -t, --t			- Run Binary Unit Tests
            "
}  

	
case $1 in
        -b|--build)
            case $2 in
                -f|--full)
                    rm -rf cmake-build-debug/
                    mkdir cmake-build-debug && cd cmake-build-debug
                    cmake ../ && make && cd ../
                ;;
                *)
                cd cmake-build-debug && make && cd ../
            esac
            
        ;;
        -g|--game)
            cd cmake-build-debug/bin && ./GAME && cd ../../
        ;;
        -t|--test)
            cd cmake-build-debug/test/bin && ./GAME_tst && cd ../../../
        ;;
        -h|--help|*)
            show_help_message
        ;;
        esac