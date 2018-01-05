#!/bin/bash

## Golden Image Generation ##

# File Conversion
echo ".jpg to .jpg"
../build/bin/MIA ../resources/test-images/snaily.jpg golden-images/snail_from_jpg.jpg

echo ".jpg to .png"
../build/bin/MIA ../resources/test-images/snaily.jpg golden-images/snail_from_jpg.png

echo ".jpg to .jpeg"
../build/bin/MIA ../resources/test-images/snaily.jpg golden-images/snail_from_jpg.jpeg

echo ".jpeg to .jpg"
../build/bin/MIA ../resources/test-images/snaily.jpeg golden-images/snail_from_jpeg.jpg

echo ".jpeg to .png"
../build/bin/MIA ../resources/test-images/snaily.jpeg golden-images/snail_from_jpeg.png

echo ".jpeg to .jpeg"
../build/bin/MIA ../resources/test-images/snaily.jpeg golden-images/snail_from_jpeg.jpeg

echo ".png to .jpg"
../build/bin/MIA ../resources/test-images/colorCircles.png golden-images/circles_from_png.jpg

echo ".png to .png"
../build/bin/MIA ../resources/test-images/colorCircles.png golden-images/circles_from_png.png

echo ".png to .jpeg"
../build/bin/MIA ../resources/test-images/colorCircles.png golden-images/circles_from_png.jpeg

# Test each function individually
echo "Sharpen 2.0"
../build/bin/MIA ../resources/test-images/snaily.jpg -sharpen 2.0 golden-images/sharp_snail.jpg

echo "Sharpen 5.0"
../build/bin/MIA ../resources/test-images/snaily.jpg -sharpen 5.0 golden-images/sharper_snail.jpg

echo "Edge Detect"
../build/bin/MIA ../resources/test-images/snaily.jpg -edge golden-images/edge_snail.jpg

echo "Threshold 0"
../build/bin/MIA ../resources/test-images/snaily.jpg -threshold 0  golden-images/thresh00_snail.jpg

echo "Threshold 0.5"
../build/bin/MIA ../resources/test-images/snaily.jpg -threshold 0.5  golden-images/thresh05_snail.jpg

echo "Threshold 1"
../build/bin/MIA ../resources/test-images/snaily.jpg -threshold 1  golden-images/thresh10_snail.jpg

echo "Quantize 4"
../build/bin/MIA ../resources/test-images/snaily.jpg -quantize 4  golden-images/quant4_snail.jpg

echo "Quantize 8"
../build/bin/MIA ../resources/test-images/snaily.jpg -quantize 8  golden-images/quant8_snail.jpg

echo "Blur 2.0"
../build/bin/MIA ../resources/test-images/snaily.jpg -blur 2.0 golden-images/blur2_snail.jpg

echo "Blur 5.0"
../build/bin/MIA ../resources/test-images/snaily.jpg -blur 5.0 golden-images/blur5_snail.jpg

echo "Saturate 2.0"
../build/bin/MIA ../resources/test-images/snaily.jpg -saturate 2.0 golden-images/sat2_snail.jpg

echo "Saturate -1.0"
../build/bin/MIA ../resources/test-images/snaily.jpg -saturate -1.0 golden-images/satinv_snail.jpg

echo "Channels 2 1 1"
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 2 1 1 golden-images/red_snail.jpg

echo "Channels 1 2 1"
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 1 2 1 golden-images/green_snail.jpg

echo "Channels 1 1 2"
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 1 1 2 golden-images/blue_snail.jpg

# Compound Functions
echo "Channels 2 1 1 Quantize 4"
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 2 1 1 -quantize 4 golden-images/red_quant4_snail.jpg

echo "Quantize 4 Channels 2 1 1"
../build/bin/MIA ../resources/test-images/snaily.jpg -quantize 4 -channel 2 1 1 golden-images/quant4_red_snail.jpg

echo "Sharpen 2.0 Saturate 2.0"
../build/bin/MIA ../resources/test-images/snaily.jpg -sharpen 2.0 -saturate 2.0 golden-images/sharp_sat2_snail.jpg

echo "Saturate 2.0 Sharpen 2.0"
../build/bin/MIA ../resources/test-images/snaily.jpg -saturate 2.0 -sharpen 2.0 golden-images/sat2_sharp_snail.jpg

echo "Blur 2.0 Threshold 0.5"
../build/bin/MIA ../resources/test-images/snaily.jpg -blur 2.0 -threshold 0.5 golden-images/blur2_thresh05_snail.jpg

echo "Threshold 0.5 Blur 2.0"
../build/bin/MIA ../resources/test-images/snaily.jpg -threshold 0.5 -blur 2.0 golden-images/thresh05_blur2_snail.jpg

echo "Edge Detect Channels 2 1 1"
../build/bin/MIA ../resources/test-images/snaily.jpg -edge -channel 2 1 1 golden-images/edge_red_snail.jpg

echo "Channels 2 1 1 Edge Detect"
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 2 1 1 -edge golden-images/red_edge_snail.jpg

# Image Stack
echo "Channels 2 1 1 Quantize 4 Brainstack"
../build/bin/MIA ../resources/test-images/brainstack/mrbrain-8bit090.png -channel 2 1 1 -quantize 4 golden-images/red_quant4_brain090.jpg

echo .jpg to .jpg
../build/bin/MIA ../resources/test-images/snaily.jpg golden-images/snail_from_jpg.jpg

echo .jpg to .png
../build/bin/MIA ../resources/test-images/snaily.jpg golden-images/snail_from_jpg.png

echo .jpg to .jpeg
../build/bin/MIA ../resources/test-images/snaily.jpg golden-images/snail_from_jpg.jpeg

echo .jpeg to .jpg
../build/bin/MIA ../resources/test-images/snaily.jpeg golden-images/snail_from_jpeg.jpg

echo .jpeg to .png
../build/bin/MIA ../resources/test-images/snaily.jpeg golden-images/snail_from_jpeg.png

echo .jpeg to .jpeg
../build/bin/MIA ../resources/test-images/snaily.jpeg golden-images/snail_from_jpeg.jpeg

echo .png to .jpg
../build/bin/MIA ../resources/test-images/colorCircles.png golden-images/circles_from_png.jpg

echo .png to .png
../build/bin/MIA ../resources/test-images/colorCircles.png golden-images/circles_from_png.png

echo .png to .jpeg
../build/bin/MIA ../resources/test-images/colorCircles.png golden-images/circles_from_png.jpeg

# Test each function individually
echo Sharpen 2.0
../build/bin/MIA ../resources/test-images/snaily.jpg -sharpen 2.0 golden-images/sharp_snail.jpg

echo Sharpen 5.0
../build/bin/MIA ../resources/test-images/snaily.jpg -sharpen 5.0 golden-images/sharper_snail.jpg

echo Edge Detect
../build/bin/MIA ../resources/test-images/snaily.jpg -edge golden-images/edge_snail.jpg

echo Threshold 0
../build/bin/MIA ../resources/test-images/snaily.jpg -threshold 0  golden-images/thresh00_snail.jpg

echo Threshold 0.5
../build/bin/MIA ../resources/test-images/snaily.jpg -threshold 0.5  golden-images/thresh05_snail.jpg

echo Threshold 1
../build/bin/MIA ../resources/test-images/snaily.jpg -threshold 1  golden-images/thresh10_snail.jpg

echo Quantize 4
../build/bin/MIA ../resources/test-images/snaily.jpg -quantize 4  golden-images/quant4_snail.jpg

echo quantize 8
../build/bin/MIA ../resources/test-images/snaily.jpg -quantize 8  golden-images/quant8_snail.jpg

echo Blur 2.0
../build/bin/MIA ../resources/test-images/snaily.jpg -blur 2.0 golden-images/blurry_snail.jpg

echo Blur 5.0
../build/bin/MIA ../resources/test-images/snaily.jpg -blur 5.0 golden-images/blurrier_snail.jpg

echo Saturate 2.0
../build/bin/MIA ../resources/test-images/snaily.jpg -saturate 2.0 golden-images/sat2_snail.jpg

echo Saturate -1.0
../build/bin/MIA ../resources/test-images/snaily.jpg -saturate -1.0 golden-images/satinv_snail.jpg

echo Channels 2 1 1
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 2 1 1 golden-images/red_snail.jpg

echo Channels 1 2 1
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 1 2 1 golden-images/green_snail.jpg

echo Channels 1 1 2
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 1 1 2 golden-images/blue_snail.jpg
