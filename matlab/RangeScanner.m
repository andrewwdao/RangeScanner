clear; clc; close all;

% max size of the logged data
MAX_SIZE = 1000;

%limit of the plot
THETA_MIN = 0;  % deg
THETA_MAX = 180;% deg
RHO_MIN = 0;    % m
RHO_MAX = 100;  % m

% dummy arrays for data storage
dat_angle = zeros(1,MAX_SIZE);
dat_sonic = zeros(1,MAX_SIZE);

% create a frame for the plot
pl = polarscatter(dat_angle, dat_sonic, 'filled');

thetalim([THETA_MIN THETA_MAX]); rlim([RHO_MIN RHO_MAX]);
title('HCSR04 2D range detector');
grid on;

% link the plot with variables that will be changed real time
pl.XDataSource = 'dat_angle';
pl.YDataSource = 'dat_sonic';

% init the serial port
ser = serialport("COM3",9600,'Timeout',2);

% define the pattern
pat_reg = "[0-9].?[0-9]+"; %[0-9].?[0-9]+
% pat = digitsPattern + (""|".") + digitsPattern;

% send start signal to the MCU
pause(2); % ease the time for the serial connection to ready
write(ser,'\n',"uint8"); 
% start reading data from MCU
for n = 1:MAX_SIZE
    % read data in
    flush(ser,"input"); raw_dat = readline(ser); % wait and read the incomming data
    % process the given data
    buf_dat = regexp(raw_dat,pat_reg,'match'); %   buf_dat = extract(dat_raw,pat);
    dat_angle(n) = deg2rad(str2double(buf_dat(1)));
    dat_sonic(n) = str2double(buf_dat(2));
    
    % update the plot
    refreshdata;
    drawnow;
end