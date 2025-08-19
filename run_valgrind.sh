#!/bin/bash

echo "Compilation..."
make

echo "Lancement de valgrind avec suppression des erreurs readline..."

valgrind --suppressions=.valgrind_suppress \
         --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --trace-children=yes \
         --track-fds=yes \
         ./minishell
