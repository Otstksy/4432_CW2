device = serialport("COM12", 9600);  % Connect to Arduino via serial port

while true
    % Read incoming data from Arduino as a string
    rawData = readline(device);

    % Split the string into an array of values using the comma as a delimiter
    sensorValues = str2double(strsplit(rawData, ','));

    % Display the raw sensor values
    disp(sensorValues);

  %buttonState = sensorValues(1);
%irSensorValue = sensorValues(2);
 % ultrasonicDistance  = sensorValues(3);

    % You can send data back to Arduino here if needed
    if(sensorValues(1) == 0)
    
    % if button is pressed
    
    end

   
    pause(0.2);
end