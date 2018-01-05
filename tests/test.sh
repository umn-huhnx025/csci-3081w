#!/bin/bash

ok_count=0
bad_count=0

# Function Definitions
function test {
	if [ -e output/$1 ]; then
		# Test for correct -compare output from MIA
		if [[ `../build/bin/MIA golden-images/$1 -compare output/$1` = 0 ]]; then
			echo FAILED: Incorrect output produced
			bad_count=$[bad_count + 1]
		else
			echo OK
			ok_count=$[ok_count + 1]
		fi
	else
		echo FAILED: Output file does not exist
		bad_count=$[bad_count + 1]
	fi
}

function test-invalid {
	# Test MIA return code, make sure it fails
	if [[ `../build/bin/MIA ../resources/test-images/snaily.jpg $1 output/SHOULD_NOT_EXIST.jpg; echo $?` = 0 ]]; then
		echo FAILED
		bad_count=$[bad_count + 1]
	else
		echo OK
		ok_count=$[ok_count + 1]
	fi
}

## Create output dir
mkdir -p output

### VALID INPUT ###
echo -e "\n<----- Test File Conversion ----->\n"
echo -n ".jpg to .jpg ... "
../build/bin/MIA ../resources/test-images/snaily.jpg output/snail_from_jpg.jpg
test snail_from_jpg.jpg

echo -n ".jpg to .jpeg ... "
../build/bin/MIA ../resources/test-images/snaily.jpg output/snail_from_jpg.jpeg
test snail_from_jpg.jpeg

echo -n ".jpg to .png ... "
../build/bin/MIA ../resources/test-images/snaily.jpg output/snail_from_jpg.png
test snail_from_jpg.png

echo -n ".jpeg to .jpg ... "
../build/bin/MIA ../resources/test-images/snaily.jpeg output/snail_from_jpeg.jpg
test snail_from_jpeg.jpg

echo -n ".jpeg to .jpeg ... "
../build/bin/MIA ../resources/test-images/snaily.jpeg output/snail_from_jpeg.jpeg
test snail_from_jpeg.jpeg

echo -n ".jpeg to .png ... "
../build/bin/MIA ../resources/test-images/snaily.jpeg output/snail_from_jpeg.png
test snail_from_jpeg.png

echo -n ".png to .jpg ... "
../build/bin/MIA ../resources/test-images/colorCircles.png output/circles_from_png.jpg
test circles_from_png.jpg

echo -n ".png to .jpeg ... "
../build/bin/MIA ../resources/test-images/colorCircles.png output/circles_from_png.jpeg
test circles_from_png.jpeg

echo -n ".png to .png ... "
../build/bin/MIA ../resources/test-images/colorCircles.png output/circles_from_png.png
test circles_from_png.png

echo -e "\n<----- Test Functions Inidividually ----->\n"
# Test Help
echo -n "Help ... "
if [[ `../build/bin/MIA -h; echo $?` = 1 ]]; then
	echo FAILED
	bad_count=$[bad_count + 1]
else
	echo OK
	ok_count=$[ok_count + 1]
fi

echo -n "Sharpen 2.0 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -sharpen 2.0 output/sharp_snail.jpg
test sharp_snail.jpg

echo -n "Sharpen 5.0 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -sharpen 5.0 output/sharper_snail.jpg
test sharper_snail.jpg

echo -n "Edge Detect ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -edge output/edge_snail.jpg
test edge_snail.jpg

echo -n "Threshold 0 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -threshold 0  output/thresh00_snail.jpg
test thresh00_snail.jpg

echo -n "Threshold 0.5 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -threshold 0.5  output/thresh05_snail.jpg
test thresh05_snail.jpg

echo -n "Threshold 1.0 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -threshold 1  output/thresh10_snail.jpg
test thresh10_snail.jpg

echo -n "Quantize 4 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -quantize 4  output/quant4_snail.jpg
test quant4_snail.jpg

echo -n "Quantize 8 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -quantize 8  output/quant8_snail.jpg
test quant8_snail.jpg

echo -n "Blur 2.0 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -blur 2.0 output/blur2_snail.jpg
test blur2_snail.jpg

echo -n "Blur 5.0 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -blur 5.0 output/blur5_snail.jpg
test blur5_snail.jpg

echo -n "Saturate 2.0 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -saturate 2.0 output/sat2_snail.jpg
test sat2_snail.jpg

echo -n "Saturate -1.0 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -saturate -1.0 output/satinv_snail.jpg
test satinv_snail.jpg

echo -n "Channels 2 1 1 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 2 1 1 output/red_snail.jpg
test red_snail.jpg

echo -n "Channels 1 2 1 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 1 2 1 output/green_snail.jpg
test green_snail.jpg

echo -n "Channels 1 1 2 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 1 1 2 output/blue_snail.jpg
test blue_snail.jpg

echo -e "\n<----- Test Compound Functions ----->\n"
echo -n "Channels 2 1 1 Quantize 4 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 2 1 1 -quantize 4 output/red_quant4_snail.jpg
test red_quant4_snail.jpg

echo -n "Quantize 4 Channels 2 1 1 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -quantize 4 -channel 2 1 1 output/quant4_red_snail.jpg
test quant4_red_snail.jpg

echo -n "Sharpen 2.0 Saturate 2.0 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -sharpen 2.0 -saturate 2.0 output/sharp_sat2_snail.jpg
test sharp_sat2_snail.jpg

echo -n "Saturate 2.0 Sharpen 2.0 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -saturate 2.0 -sharpen 2.0 output/sat2_sharp_snail.jpg
test sat2_sharp_snail.jpg

echo -n "Blur 2.0 Threshold 0.5 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -blur 2.0 -threshold 0.5 output/blur2_thresh05_snail.jpg
test blur2_thresh05_snail.jpg

echo -n "Threshold 0.5 Blur 2.0 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -threshold 0.5 -blur 2.0 output/thresh05_blur2_snail.jpg
test thresh05_blur2_snail.jpg

echo -n "Edge Detect Channels 2 1 1 ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -edge -channel 2 1 1 output/edge_red_snail.jpg
test edge_red_snail.jpg

echo -n "Channels 2 1 1 Edge Detect ... "
../build/bin/MIA ../resources/test-images/snaily.jpg -channel 2 1 1 -edge output/red_edge_snail.jpg
test red_edge_snail.jpg

echo -e "\n<----- Test Stack Functionality ----->\n"
../build/bin/MIA ../resources/test-images/brainstack/mrbrain-8bit090.png -channel 2 1 1 -quantize 4 output/red_quant4_brain090.jpg

count=90
for image in output/*brain*
do
	echo -n "Channels 2 1 1 Quantize 4 Brain Stack "
	printf "%03d ... " $count
	test $(basename $image)
	count=$[ count + 1 ]
done


### INVALID INPUT
# Wrong Arguments for each function
echo -e "\n<----- Test Invalid Input ----->\n"
echo -n "Sharpen No Arg ... "
test-invalid "-sharpen"
echo -n "Sharpen Missing hyphen ... "
test-invalid "sharpen 2.0"
echo -n "Sharpen Too Many Args ... "
test-invalid "-sharpen 2.0 2.0"
echo -n "Sharpen String ... "
test-invalid "-sharpen string"

echo -n "Edge Detect With Arg ... "
test-invalid "-edge 1.0"
echo -n "Edge Missing Hyphen ... "
test-invalid "edge"
echo -n "Edge Detect String ... "
test-invalid "-edge string"

echo -n "Threshold No Arg... "
test-invalid "-threshold"
echo -n "Threshold Missing Hyphen ... "
test-invalid "threshold 0.5"
echo -n "Threshold 0.5 0.5 ... "
test-invalid "-threshold Too Many Args"
echo -n "Threshold String ... "
test-invalid "-threshold string"

echo -n "Quantize No Arg... "
test-invalid "-quantize"
echo -n "Quantize Missing Hyphen ... "
test-invalid "quantize 4"
echo -n "Quantize Too Many Args ... "
test-invalid "-quantize 4 4"
echo -n "Quantize String ... "
test-invalid "-quantize string"

echo -n "Blur No Arg ... "
test-invalid "-blur"
echo -n "Blur Missing Hyphen ... "
test-invalid "blur 2"
echo -n "Blur Too Many Args ... "
test-invalid "-blur 2 2"
echo -n "Blur String ... "
test-invalid "-blur string"

echo -n "Saturate No Arg ... "
test-invalid "-saturate"
echo -n "Saturate Missing Hyphen ... "
test-invalid "saturate 2"
echo -n "Saturate Too Many Args ... "
test-invalid "-saturate 2 2"
echo -n "Saturate String ... "
test-invalid "-saturate string"

echo -n "Channels No Args ... "
test-invalid "-channel"
echo -n "Channels One Arg ... "
test-invalid "-channel 1"
echo -n "Channels Two Args ... "
test-invalid "-channel 1 1"
echo -n "Channels Too Many Args ... "
test-invalid "channel 2 1 1 1"
echo -n "Channels Missing Hyphen ... "
test-invalid "channel 2 1 1"
echo -n "Channels String ... "
test-invalid "-channel string string string"

echo -n "Stack Image Out of Range 0 ... "
if [[ `../build/bin/MIA resources/test-images/brainstack/mrbrain-8bit000.png output/_SHOULD_NOT_EXIST.jpg; echo $?` = 0 ]]; then
	echo FAILED
	bad_count=$[bad_count + 1]
else
	echo OK
	ok_count=$[ok_count + 1]
fi

echo -n "Stack Image Out of Range 100 ... "
if [[ `../build/bin/MIA resources/test-images/brainstack/mrbrain-8bit100.png output/_SHOULD_NOT_EXIST.jpg; echo $?` = 0 ]]; then
	echo FAILED
	bad_count=$[bad_count + 1]
else
	echo OK
	ok_count=$[ok_count + 1]
fi

echo -n "No Input File Given ... "
if [[ `../build/bin/MIA -sharpen 2.0 output/_SHOULD_NOT_EXIST.jpg; echo $?` = 0 ]]; then
	echo FAILED
	bad_count=$[bad_count + 1]
else
	echo OK
	ok_count=$[ok_count + 1]
fi

echo -n "No Output File Given ... "
if [[ `../build/bin/MIA ../resources/test-images/snaily.jpg -sharpen 2.0; echo $?` = 0 ]]; then
	echo FAILED
	bad_count=$[bad_count + 1]
else
	echo OK
	ok_count=$[ok_count + 1]
fi

echo -n "No Files Given ... "
if [[ `../build/bin/MIA -sharpen 2.0; echo $?` = 0 ]]; then
	echo FAILED
	bad_count=$[bad_count + 1]
else
	echo OK
	ok_count=$[ok_count + 1]
fi

echo Passed $ok_count/`expr $ok_count + $bad_count` Tests
