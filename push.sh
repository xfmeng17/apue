#!/bin/bash

# rm all .out file
find . -name "*.out" | xargs rm
find . -name "*core" | xargs rm

MESSAGE=`date +"%Y-%m-%d %T"`
git add .
git commit -m "${MESSAGE}"
git push origin master

