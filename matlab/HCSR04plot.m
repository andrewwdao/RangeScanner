clear; clc; close all;

% max size of the logged data
MAX_SIZE = 1000;

%limit of the plot
Y_MAX = 200;
Y_MIN = 0;
tmin = datetime("now",'InputFormat', 'HH:mm:ss') + seconds(2);
tmax = tmin + seconds(60);

% dummy arrays for data storage
dat_angle = zeros(1,app.MAX_SIZE);
dat_sonic = zeros(1,app.MAX_SIZE);
timestamp = NaN(1,app.MAX_SIZE);

% create a frame for the plot
pl = plot(timestamp, dat_sonic,'LineWidth',2);
xlim([tmin tmax]); ylim([Y_MIN Y_MAX]);
xlabel('Time'); ylabel('HCSR04 echo time');
title('HCSR04 echo time plot');
grid on;

% link the plot with variables that will be changed real time
pl.XDataSource = 'timestamp';
pl.YDataSource = 'dat_sonic';

% init the serial port
ser = serialport("COM8",9600,'Timeout',2);
% define the pattern
pat = (""|"-") + digitsPattern + (""|".") + digitsPattern; % pat_reg = "-?[0-9]+.?[0-9]+"

% start reading data from MCU
for n = 1:MAX_SIZE
    % read data in
    dat_raw = readline(ser); % wait and read the incomming data
    timestamp(n) = datetime("now",'InputFormat', 'HH:mm:ss');
    % process the given data
    dat_arr = extract(dat_raw,pat); % regexp(data_raw,pat_reg); is also a good method
    dat_angle(n) = str2double(dat_arr(1));
    dat_sonic(n) = str2double(dat_arr(2));
    
    % update the plot
    refreshdata;
    drawnow;
end