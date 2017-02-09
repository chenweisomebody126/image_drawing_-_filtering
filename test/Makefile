CMD_PATH = ../
EXE = ./$(CMD_PATH)build/bin/MIA

all: tests

tests: pass bad filters filter-chains batch comparison

#Pass Through
pass:
	@echo "testing pass through"
	@- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg snaily-out-pass-through.jpg;  echo $$?
	@- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png color-circles-pass-through.png; echo $$?

#Bad Input
bad:
	@echo "testing bad input"
	#directory
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.foo bad-input-extension.jpg; echo $$?
	- $(EXE) $(CMD_PATH)does/not/exist.jpg input-does-not-exist.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png color-circles.foo; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png does/not/exist.png; echo $$?
	#blur
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -blur -1.0 blur-case0.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -blur -1.0 blur-case1.png; echo $$?
	#edge
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -edge 5.0 bad-edge-parameters1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.jpg -edge 5.0 bad-edge-parameters2.png; echo $$?
	#threshold
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -threshold -0.1 bad-threshold-parameters1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -threshold 1.1 bad-threshold-parameters2.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -threshold 0 bad-threshold-parameters3.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -threshold 1 bad-threshold-parameters4.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -threshold 0.5 bad-threshold-parameters5.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -threshold 0.5 bad-threshold-parameters5.png; echo $$?
	#saturate
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -saturate -11 bad-saturate-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -saturate -11 bad-saturate-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -saturate 11 bad-saturate-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -saturate 11 bad-saturate-case2.png; echo $$?
	#channel
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -channel 1.0 1.0 bad-channel-parameters.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -channel 11.0 0.0 1.0 bad-channel-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -channel 11.0 0.0 1.0 bad-channel-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -channel 11.0 0.0 1.0 bad-channel-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -channel 11.0 0.0 1.0 bad-channel-case2.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -channel 0.0 0.0 11.0 bad-channel-case3.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -channel 0.0 0.0 11.0 bad-channel-case3.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -channel -1.0 0.0 0.0 bad-channel-case4.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -channel -1.0 0.0 0.0 bad-channel-case4.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -channel 0.0 -1.0 1.0 bad-channel-case5.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -channel 0.0 -1.0 1.0 bad-channel-case5.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -channel 0.0 0.0 -1.0 bad-channel-case6.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -channel 0.0 0.0 -1.0 bad-channel-case6.png; echo $$?
	#quantize
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -quantize 257 bad-quantize-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -quantize 257 bad-quantize-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -quantize 1 bad-quantize-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -quantize 1 bad-quantize-case2.png; echo $$?
	#sharpen
	- $(EXE) $(CMD_PATH)-sharpen 5.0 missing-input-file.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -sharpen 5.0; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -sharpen -1.0 bad-sharpen-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -sharpen 101.0 bad-sharpen-case1.png; echo $$?
	#compare
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg resources/test-images/snaily.jpg -compare; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily -compare; echo $$?
	#batch
	- $(EXE) $(CMD_PATH)resources/test-images/brainstack/mr-brain-8bit##.png bad-brainstack1/mr-brain8bit##.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/brainstack/mr-brain-8bit###.png bad-brainstack2/mr-brain8bit##.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/brainstack/bad-brainstack3/mr-brain8bit###.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/brainstack/mr-brain-8bit###.pngbad-brainstack4/; echo $$?
	#batch
	./build/bin/MIA resources/test-images/brainstack/mrbrain-8bit###.png –sharpen -1 output/sharp-brain###.jpg; echo $$?

comparison:
		@echo "testing comparison"
		- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -compare resources/test-images/snaily.jpg; echo $$?; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -saturate 0 golden_images/golden_saturate-case2.jpg; echo $$?
		- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -compare resources/test-images/colorCircles.png; echo $$?

#Filters(blur, edge, threshold, saturate, quantize)
filters:
	@echo "testing filters::blur"
	#filters::blur
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -blur 0.0 blur-case0.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -blur 0.0 blur-case0.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -blur 5.0 blur-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -blur 5.0 blur-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -blur 10.0 blur-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -blur 10.0 blur-case2.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -blur 20.0 blur-case3.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -blur 20.0 blur-case3.png; echo $$?
	#filters::edge
	@echo "testing filters::edge"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -edge detect-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -edge detect-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -edge detect-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -edge detect-case1.jpg; echo $$?
	#filters::threshold
	@echo "testing filters::threshold"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -threshold 0.1 threshold-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -threshold 0.1 threshold-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -threshold 0.8 threshold-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -threshold 0.8 threshold-case2.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -threshold 1.0 threshold-case3.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -threshold 1.0 threshold-case3.png; echo $$?
	#filters::saturate
	@echo "testing filters::saturate"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -saturate -10 saturate-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -saturate -10 saturate-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -saturate 0 saturate-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -saturate 0 saturate-case2.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -saturate 10 saturate-case3.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -saturate 10 saturate-case3.png; echo $$?
	#filters::quantize
	@echo "testing filters::quantize"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -quantize 2 quantize-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -quantize 2 quantize-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -quantize 4 quantize-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -quantize 4 quantize-case2.png; echo $$?
	@echo "testing filters::sharpen"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -sharpen 5.0 sharpen-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -sharpen 5.0 sharpen-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -sharpen 10.0 sharpen-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -sharpen 10.0 sharpen-case2.png; echo $$?
	@echo "tesing filters::channel"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -channel 0.0 0.0 1.0 channel-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -channel 0.0 0.0 1.0 channel-case1.png; echo $$?
	if [ -d "$golden_images" ]; \
	then \
		@echo "comparing blured images with golden blured images" \
		- $(EXE) $(CMD_PATH)resources/test-images/blur-case1.jpg -compare golden_images/golden_blur-case1.jpg; echo $$? \
		- $(EXE) $(CMD_PATH)resources/test-images/blur-case1.jpg -compare golden_images/gloden_blur-case1.png; echo $$? \
		@echo "comparing edge detect images with golden edge detect images" \
		- $(EXE) $(CMD_PATH)resources/test-images/detect-case1.jpg -compare golden_images/golden_detect-case1.jpg; echo $$? \
		- $(EXE) $(CMD_PATH)resources/test-images/detect-case1.png -compare golden_images/gloden_detect-case1.png; echo $$? \
		@echo "comparing threshold images with golden threshold images" \
		- $(EXE) $(CMD_PATH)resources/test-images/threshold-case1.jpg-compare golden_images/golden_threshold-case1.jpg; echo $$? \
		- $(EXE) $(CMD_PATH)resources/test-images/threshold-case1.png -compare golden_images/gloden_threshold-case1.png; echo $$? \
		@echo "comparing saturate images with golden saturate images" \
		- $(EXE) $(CMD_PATH)resources/test-images/saturate-case1.jpg-compare golden_images/golden_saturate-case1.jpg; echo $$? \
		- $(EXE) $(CMD_PATH)resources/test-images/saturate-case1.png -compare golden_images/gloden_saturate-case1.png; echo $$? \
		@echo "comparing quantize images with golden quantize images" \
		- $(EXE) $(CMD_PATH)resources/test-images/quantize-case1.jpg-compare golden_images/golden_quantize-case1.jpg; echo $$? \
		- $(EXE) $(CMD_PATH)resources/test-images/quantize-case1.png -compare golden_images/gloden_quantize-case1.png; echo $$? \
		@echo "comparing sharpen images with golden sharpen images" \
		- $(EXE) $(CMD_PATH)resources/test-images/sharpen-case1.jpg-compare golden_images/golden_sharpen-case1.jpg; echo $$? \
		- $(EXE) $(CMD_PATH)resources/test-images/sharpen-case1.png -compare golden_images/gloden_sharpen-case1.png; echo $$? \
		@echo "comparing channel images with golden channel images" \
		- $(EXE) $(CMD_PATH)resources/test-images/channel-case1.jpg-compare golden_images/golden_channel-case1.jpg; echo $$? \
		- $(EXE) $(CMD_PATH)resources/test-images/channel-case1.png -compare golden_images/gloden_channel-case1.png; echo $$? \
	else
		#golden images do not exist, skip comparison with golden images
	fi

#Filter Chaining
filter-chains:
	@echo "testing filter chaining"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -saturate 0 -threshold 0.8 -quantize 2 chained-saturate-threshold-quantize.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -saturate 0 -threshold 0.8 -quantize 2 chained-saturate-threshold-quantize.png; echo $$?

#Batch Processing
batch:
	@echo "testing batch processing"
	- $(EXE) $(CMD_PATH)resources/test-images/brainstack/mrbrain-8bit###.png -edge brainstack-edge/###.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/brainstack/mrbrain-8bit###.png -quantize brainstack-quantize/###.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/brainstack/mrbrain-8bit###.png -compare resources/test-images/brainstack/mrbrain-8bit###.png; echo $$?

golden:
	-rm ./golden_images
	mkdir ./golden_images
	@echo "generating golden_blur_images"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -blur 0.0 golden_images/golden_blur-case0.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -blur 0.0 golden_images/golden_blur-case0.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -blur 5.0 golden_images/golden_blur-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -blur 5.0 golden_images/golden_blur-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -blur 10.0 golden_images/golden_blur-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -blur 10.0 golden_images/golden_blur-case2.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -blur 20.0 golden_images/golden_blur-case3.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -blur 20.0 golden_images/golden_blur-case3.png; echo $$?
	@echo "generating golden_edge_images"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -edge golden_images/golden_detect-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -edge golden_images/golden_edge detect-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -edge golden_images/golden_detect-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -edge golden_images/golden_edge detect-case1.jpg; echo $$?
	@echo "generating golden_threshold_images"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -threshold 0.1 golden_images/golden_threshold-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -threshold 0.1 golden_images/golden_threshold-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -threshold 0.8 golden_images/golden_threshold-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -threshold 0.8 golden_images/golden_threshold-case2.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -threshold 1.0 golden_images/golden_threshold-case3.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -threshold 1.0 golden_images/golden_threshold-case3.png; echo $$?
	@echo "generating golden_saturate_images"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -saturate -10 golden_images/golden_saturate-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -saturate -10 golden_images/golden_saturate-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -saturate 0 golden_images/golden_saturate-case2.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -saturate 10 golden_images/golden_saturate-case3.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -saturate 10 golden_images/golden_saturate-case3.png; echo $$?
	@echo "generating golden_quantize_images"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -quantize 2 golden_images/golden_quantize-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -quantize 2 golden_images/golden_quantize-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -quantize 4 golden_images/golden_quantize-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -quantize 4 golden_images/golden_quantize-case2.png; echo $$?
	@echo "generating golden_sharpen_images"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -sharpen 5.0 golden_images/golden_sharpen-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -sharpen 5.0 golden_images/golden_sharpen-case1.png; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -sharpen 10.0 golden_images/golden_sharpen-case2.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -sharpen 10.0 golden_images/golden_sharpen-case2.png; echo $$?
	@echo "generating golden_channel_images"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -channel 0.0 0.0 1.0 golden_images/golden_channel-case1.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -channel 0.0 0.0 1.0 golden_images/golden_channel-case1.png; echo $$?
	@echo "generating golden_filter_chaining_images"
	- $(EXE) $(CMD_PATH)resources/test-images/snaily.jpg -saturate 0 -threshold 0.8 -quantize 2 golden_images/golden_chained-saturate-threshold-quantize.jpg; echo $$?
	- $(EXE) $(CMD_PATH)resources/test-images/colorCircles.png -saturate 0 -threshold 0.8 -quantize 2 golden_images/golden_chained-saturate-threshold-quantize.png; echo $$?
