###For users: an initial tutorial with links to example data. 
####Converting and Segmenting a CT Scan Using Mia
discusses how to convert a sequenced image stack saved as a set of numbered images in a directory to a quantized version that has 4 tissue types. The approach for this should be to first slightly blur the image (to reduce noise), then quantize the result into 4 segments, then save the resulting images to a new directory. The tutorial should reference the sample data that we have provided along with the iteration #3 support code. Provide two sets of instructions, using both the graphical user interface as well as the command line interface. (Assume that the reader knows how to open a terminal and use cd/ls, but feel free to provide them with copy-and-paste commands.) 
Use MIA Graphic Mode to Convert and Segment a CT Scan
#####Step 1: Navigate to the root directory
Please first open your terminal and use cd to navigate to the folder where you have all the files downloaded from our Github.
#####Step 2: Install MIA
Following step #1, you should be now in root directory. Type following command on your terminal to install MIA:
make install
#####Step 3: Open MIA Graphic Mode
Following above steps, you should be now in root directory. Type following command on your terminal to open MIA Graphic Mode:
./build/bin/MIA
Now you should see the windows of MIA Graphic Mode. We will refer the left windows titled “MIA” as canvas and the right windows titled “Controls” as control panel:

#####Step 4: Load the CT scan picture to MIA
Using [Image I/O] panel in control panel, you can navigate among folders to find the CT scan picture you want to modify, right click the filename and click [Load Canvas] button.
Now you should see your CT scan picture shown on canvas:

![image](https://github.umn.edu/umn-csci-3081F16/repo-group-A03/blob/master/doc/images/original_brain.png)

#####Step 5: Reduce noise of the CT scan picture by using Blur function
You can utilize Blur panel in control panel to reduce noise of your CT scan picture. To blur the picture on canvas, type a number into the textbox in Blur panel and click [Apply] button.
Now you should see that your CT scan picture have been blurred on canvas:

![image](https://github.umn.edu/umn-csci-3081F16/repo-group-A03/blob/master/doc/images/blur_brain.png)

#####Step 6: Quantize the CT scan picture into 4 segments using Quantize function
You can utilize Quantize panel in control panel  to segment your CT scan picture. To Quantize the picture on canvas to 4 segments, type 4 into  the textbox in Quantize panel and click [Apply] button. Now you should see that your CT scan picture have been quantized to 4 segments on canvas:

![image](https://github.umn.edu/umn-csci-3081F16/repo-group-A03/blob/master/doc/images/quantize_brain.png)

#####Step 7: Save the result picture
Using [Image I/O] panel in control panel, you can navigate among folders to find the directory where you want to save the result picture. If you want to change the picture name rather than the original picture name, type the desired picture name into textbox under Image I/O panel. Then you can click [Save Canvas] button to save the picture.
Step 8: Repeat step 4 - 7 until you have processes all CT scan pictures


Use MIA Command Line Mode to Convert and Segment a CT Scan

###Project Design: 
    ‘Src’ is the root directory of the project. Under the root directory we have app and lib. App     
    has both FlashPhotoApp and MIA apps. Each app has its own src and make file so it can 
    compile on its own. Next to app there lib directory. Lib directory has libimgtools inside of it.
    Libimgtools contains all files and classes that are common to both FlashPhotoApp and MIA apps.
