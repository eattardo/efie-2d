% Load Peterson Results
clear all;
clc;
close all;

% Figure 2.14 Peterson's book
xe=       [-0.15 -0.14 -0.13 -0.12 -0.1    -0.09     -0.06 -0.0275  0    0.0325  0.06  0.08   0.09 0.10725 0.125  0.155];    %x-axis exact solution
ExactAbs= [0.77  0.73  0.7   0.67  0.60125 0.600625 0.65  0.78    0.9625 1.1375 1.275 1.3725 1.4  1.45    1.4625 1.425]; %abs exact solution
ExactPhase=[68.75 60.31 54.6875 49.8625 32.1875 18.125 -10 -32.5  -49.375 -63.4175 -71.875 -77.5 -80.3125 -83.125 -88.75 -97.1875]; %phae exact solution

% Load EFIE2D data results on line y=0 (example of Figure 2.14)
E = load("PetersonCyl_Y0.output");

% Get x, y of the mesh
xEFIE2D = E(:,1);
Ez = abs(complex(E(:,3), E(:,4)));
Ezph= atan2(E(:,4),E(:,3));

figure;
hold on, title('Ez abs')
plot(xe, ExactAbs,'k*--'),grid,
plot(xEFIE2D,Ez,'ro--'),hold off;

figure;
hold on, title('Phase')
plot(xe, ExactPhase,'k*--'),grid,
plot(xEFIE2D,rad2deg(Ezph),'ro--'),hold off;
