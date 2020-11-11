function pic = encrypt(grain, image, key)

          % row X column X 3
        
          temp = image;
          temp1 = temp;
          pic1 =  temp;
          
          base64 = matlab.net.base64encode(key);

          % column transposition

          len1 = strlength(base64);
          len2 = size(temp,2);

          if (len2 < len1)
              base64 = base64(1: len2);
          elseif (len2 > len1)
              s = base64;
              for i = 1:len2/len1
                  s = strcat(s,base64);
              end
              base64=s(1:len2);
          end
      
          int_max = size(temp,2) / grain;
          hash_set = java.util.HashSet(int_max);
          s=""
         for i=1:strlength(base64)
             s=s+double(base64(i));
         end
         ch=convertStringsToChars(s);
         arr=[];
         index=1;
          for i = 1:strlength(ch)
              sb1 = "";
              for j = i:strlength(ch)
                  sb1 = sb1+ch(j); 
                  k = str2num(sb1);
                  if (k < int_max)
                      if (~hash_set.contains(k))
                          hash_set.add(k);
                          arr(index)=k;
                          index=index+1;
                          break;
                      end
                  else
                      while (k >= int_max || (k >= 0 && (hash_set.contains(k))))
                          k = k-1;
                      end
                      if (k>=0 && ~ hash_set.contains(k))
                          hash_set.add(k);
                          arr(index)=k;
                          index=index+1;
                      end
                      break;
                  end
              end
              if (hash_set.size() == int_max)
                  break;
              end
          end
              
          for i = 0:(int_max-1)
              if(~hash_set.contains(i))
                  arr(index)=i;
                  index=index+1;
                  hash_set.add(i);
              end
          end
          index=1;
          col = 1;
          while(index<=size(arr,2))
              num = arr(index) * grain;
              for i = 1: grain
                  for j = 1: size(temp,1)
                      px_red = temp(j,num + i,1);
                      px_green = temp(j,num + i,2);
                      px_blue = temp(j,num + i,3);

                      temp1(j,col,1) = px_red;
                      temp1(j,col,2) = px_green;
                      temp1(j,col,3) = px_blue;
                  end
                  col = col+1;
              end
              index=index+1;
          end

          % row transposition

          len1 = strlength(base64);
          len2 = size(temp,1);

          if (len2 < len1)
              base64 = base64(1:len2);
          elseif (len2 > len1)
              s = base64;
              for i = 1:len2/len1
                  s = strcat(s,base64);
              end
              base64 = s(1:len2);
          end
          
          int_max = size(temp,1) / grain;
          hash_set = java.util.HashSet(int_max);
          
         s=""
         for i=1:strlength(base64)
             s=s+double(base64(i));
         end
         ch=convertStringsToChars(s);
         arr=[];
         index=1;
           for i = 1:strlength(ch)
              sb1 = "";
              for j = i:strlength(ch)
                  sb1 = sb1+ch(j); 
                  k = str2num(sb1);
                  if (k < int_max)
                      if (~hash_set.contains(k))
                          hash_set.add(k);
                          arr(index)=k;
                          index=index+1;
                          break;
                      end
                  else
                      while (k >= int_max || (k >= 0 && (hash_set.contains(k))))
                          k = k-1;
                      end
                      if (k>=0 && ~ hash_set.contains(k))
                          hash_set.add(k);
                          arr(index)=k;
                          index=index+1;
                      end
                      break;
                  end
              end
              if (hash_set.size() == int_max)
                  break;
              end
           end
              
          for i = 0:(int_max-1)
              if(~hash_set.contains(i))
                  hash_set.add(i);
                  arr(index)=i;
                  index=index+1;
              end
          end

          row = 1;
          index=1;
          while(index<=size(arr,2))
              num =arr(index) * grain;
              for i = 1: grain
                  for j = 1: size(temp,2)
                      px_red = temp1(num + i,j,1);
                      px_green = temp1(num + i,j,2);
                      px_blue = temp1(num + i,j,3);

                      pic1(row,j,1) = px_red;
                      pic1(row,j,2) = px_green;
                      pic1(row,j,3) = px_blue;
                  end
                  row = row+1;
              end
              index=index+1;
          end

          pic = pic1
end
 