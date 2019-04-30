# PPG-Algorithm
#Code written by Frank Din
#Program to detect hearbeat based on PPG 
#This was for my undergraduate senior design project, and I worked along side Clemente Velazquez and Sagar Bhaukaji. This is the second version of the algorithm and was based on a more robust technique to detect the heart rate than the first algorithm. The first algorithm involved detecting a certain number of hearbeat or "peaks" and multiplying by a corresponding number to get your hear rate. For example, if you took your pulse for 10 seconds, you would then multiply the number of beats you counted by 6, to get your heart rate in beats per minute (bpm). This technique was flawed because it depended on the sensor not missing any beat, or not counting too many beats.

#The current algorithm was based on the technique of a moving avarage. In this case, you would 
#1)Measure a certain number of beats or peaks (say 11 peaks) and record the time at which each peak occured from the moment you started measuring. 
#2)Take the difference in time of occurence between consecutive peak (between peak 1 and 2, peak 2 and 3 etc). These time differences represent how long it took to get to the next peak or heart beat.
#3)Take the inverse of each of the time difference vaues from above. This gives you the instantaneous frequency of each heartbeat. You should make sure your time units are seconds in order to have your frequency in hertz (Hz). Hz is cycles/beats per second and this represents how many beats would occur every second based on each heart beat detected.
#4)Take the average of the above frequency values and multiply it by 60 in order to get the heart rate value in bpm. This is only the first value.
#5)To detect the all the other heart rate values, remove some peak values from the array of peak values you had (starting with the least recent value), replace them with new peak values you just detected and repeat steps 2 - 5. This is the moving average part of the algorithm. We consistently use the average of 10 values for the heart rate calculation but we only add a few new values for every average we calculate.
