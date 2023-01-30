clear all;
close all;
clc;

puerto = serialport("COM6",19200,'timeout',5);
muestras= 5000;
i=1;

figure('Name','Grafica voltaje');
title('GRAFICA VOLTAJE ADC-SERIAL');
xlabel('Nunero de Muestras');
ylabel('Voltaje (V)');
grid on;
hold on;
ylim([-1 4]);
xlim([0 100]);

while i<=muestras

    if mod(i,100)==0;
        xlim([0 i+100]);
    end

    str_1=readline(puerto);
   
    ADC1= str2double(str_1);

voltaje1(i)=(ADC1*3.3)/4095;

plot(voltaje1,'r');
drawnow

i=i+1;

end




