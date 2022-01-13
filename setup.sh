#!/bin/bash

echo "# yacine180496.github.io" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/yacine180496/yacine180496.github.io.git
git push -u origin main