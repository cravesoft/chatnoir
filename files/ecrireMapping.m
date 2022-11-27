j=4;
for i=130:247
    pos = uint8(K == i);
    K = K.*uint8(pos == 0);
    K= K + j.*pos;
    j = j+1;
end

fid = fopen('test.txt','w');
fprintf(fid,'u8 Levels[192][256] = {\n');
for i=1:192
        fprintf(fid,'{');
       for j=1:255
           fprintf(fid,'%d,',K(i,j));
       end
       fprintf(fid,'%d},\n',K(i,256));
end
fprintf(fid,'};\n');
fclose(fid);