#!/bin/bash

#ssh -i ~/.ssh/ani.txt ubuntu@35.160.218.29 ;
sudo scp -i ~/.ssh/ani.txt 07_17NQueen.c Makefile ec2-user@34.210.150.129:/home/ec2-user/N-Queens/ ;