close all;clear all;clc;

a = arduino('COM3','Nano3','Libraries','I2C');


R_div = 1000;
VCC = 5;
angle = 0:10:90;


stoptime = 5;
order = 10;
framelen = 51;

for i = 1:length(angle)
    
    % Run the while loop for 5 sec and register data from the specific angl
    % of the flex sensor
    count = 1;
    tic 
    while toc < stoptime
        V_read0(count) = readVoltage(a,"A0");
        R_flex0(count) = R_div*(VCC/V_read0(count)-1);
        count = count + 1;
    end
    
    % Filter the data and find the mean
    rlo = smoothdata(R_flex0./1000,'rloess',framelen);
    Res_mean(i) = mean(rlo);
    
    % 
    if i < 10 
        fprintf('Data gathered for angle: %i \nThe next angle is: %i\n',angle(i),angle(i+1))
        yes_no = input('Is the flex sensor ready in the next angle? [Yes] ','s');
        if strcmp(yes_no,'Yes')
            i = i;      % Continue to recive data from the next angle
        else
            error('There was an error! You have to answer with Yes to continue')
        end
    elseif i == 10
        fprintf('Data gathered for angle: %i \n',angle(i))
    end
    clear R_flex V_read
end


% Fit data to second order polynomial
f1 = fit(Res_mean',angle','poly1');  % Fit data to curve
p1 = f1.p1;                       % first parameter in the polynom
p2 = f1.p2;                       % second parameter in the polynom
% p3 = f1.p3;                       % third parameter in the polynom


% % Plot graph for the polynom
% figure()
% plot(f1,linspace(angle(1),angle(end),1000),Res_mean)
% xlabel('Angle')
% ylabel('Resistance [k\Omega]')


% Plot the angle and resistance of the flex sensor
xlabel('Count');
ylabel('Resistance[k\Omega] ,Angle^{\circ} ');
title('Real time resistance and angle');
R = animatedline('Color','r');
ang = animatedline('Color','k');
axis tight;
legend('Resistance','Angle');
Dx=100;y1=-10;y2=120;


stop_time = 100; 
count = 1;
tic;
while(toc <= stop_time)
    % Calculate resistance from voltage
    V_read0 = readVoltage(a,"A0");
    R_flex0 = R_div*(VCC/V_read0-1)/1000;
    
    % The parameters comes from the curve fitting
    angle_plot = p1*R_flex0 + p2; 
    
    % Plot in real time
    addpoints(R,count,R_flex0);
    addpoints(ang,count,angle_plot);
    axis([count-Dx count y1 y2])
    drawnow limitrate;
    count = count + 1;
end

