port='COM7';
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end
%fprintf('opening port %s....\n',port);
mySerial=serial(port,'BaudRate', 230400.0);
fopen(mySerial);
fprintf(mySerial, '%s', '\n');
fprintf(mySerial, '%s', 'b\r\n');
len = fscanf(mySerial, '%f');
data = zeros(len,3);
for i = 1:len
    data(i,:) = fscanf(mySerial, '%f %f %f');
end

fclose(mySerial);