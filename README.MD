# Goal
A device capable of quickly measuring the OD600 of a culture tube

# Specifications
-  OD600 Range of 0.05-0.5
-  OD600 precision  of <0.02
-  Option: Functions with tubes with gradations
-  Tube to tube variability <0.02
-  Does not need to be portable, can utilize an outlet
-  Capable of measureing 1-100 samples in >15 minutes
-  Capable of being blanked against different media
-  Reads out at least 2 significant figures
-  Robust to rough handeling by user

# Checkpoints
-  Select a photodetector
-  Select a light source
-  Select splitter
-  Interface with photodetector
-  Intereface with light source
-  Determine performance parameters of system and if they meet our specifications
-  Design a user interaction method
-  Select parts for user interaction
-  Interface with parts for user interaction
-  Design chasis and wiring
-  Produce chasis and wiring
-  Code complete system
-  Analyze performance
  
#Project Title: 
**Rapid OD Detector (RODD)**
###Rough Project Description
Develop a portable/small optical density (OD) measuring device that can either sit in or near an incubator for the purpose of rapidly reading the OD of culture tubes within said incubator.

#Prodject Abstract:
A ubiquitous synthetic biology protocol is to grow liquid cultures of cells in 14mL culture tubes within a large orbital shaker incubator to a desired optical density (OD) for various experimental reasons. The challenging and at times frustrating aspect of this protocol is quantifying when the cells have reached their desired density. Traditionally, researchers either pipette samples into cuvettes and read these on a large spectrophotometer or hold each culture tube up to a light source and estimate OD based on experience. The first approach does not scale well with increasing culture tubes while the latter approach is susceptible to large errors especially at low ODs (<0.1 OD 600nm). A solution to this problem is to develop a device that sits within or on the orbital incubator that can read the OD of liquid cultures while they're within their culture tubes. By using Beer's law, an Arduino, a couple of photo detectors, and a laser, the proposed OD measuring device will be able to accurately (+/- 0.1 OD 600nm) and rapidly read out culture tube OD for the purpose of quickly quantifying if a liquid cell culture has reached its desired OD.

