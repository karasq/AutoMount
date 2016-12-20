# AutoMount
AutoMount is small application for Windows Embedded CE 6.0 that let you mount your SD card partitions. 

By default some Windows CE 6.0 devices like Mio Spirit 6970 LM do not mount partitions of SD card on booting process, 
wich make things harder if you would like to start application from your memory card on boot or from 3rd party software. 
In that case you need to physically take out you card from memory slot and put it back to trigger mouting process.

This application try to solve this problem by mouting partitions programmatically.

## How does it work? ##
It simply scans your system looking for unmouted partitions and try to mount them all (SD card partition will be the
only one in most cases). Hidden partitions and unknown file system partitions will be omited.

## How to use it? ##
It depends on your needs. Basically you need to somehow run the application on your device. 
You can try to configure your device to run AutoMount on booting process, so you will be able 
to access SD card partition from any application right after this process. Or you can run it 
on-demand e.g. through MortScript only when you need it.