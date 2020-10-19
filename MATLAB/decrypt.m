function pic = decrypt(grain, image, key)

    // row X column X 3

    temp = image;
    temp1 = copy(temp);
    pic1 = copy(temp);

    base64 = base64encode(key);

    // row transposition

    len1 = strlength(base64);
    len2 = size(temp)(0);

    if (len2 < len1)
        base64 = substr(base64, 1, len2);
    elseif (len2 > len1):
        s = base64;
        for i = 1:len2/len1
            s = strcat(s,base64);
        end
        base64 = substr(base64, 1, len2);
    end

    hash_set = java.util.HashSet;
    int_max = size(temp)(0) / grain;

    ch = double(base64);
    s = "";
    for i = 1:size(ch)(1)
        s = strcat(s,ch(i));
    end
    ch = s;

    for i = 1:strlen(ch)
        sb1 = "";
        for j = i:strlen(ch)
            sb1 = strcat(sb1,ch(j)); 
            k = str2num(sb1);
            if (k < int_max)
                if (hash_set.contains(k))
                    break;
                else
                    hash_set.add(k);
                end
            else
                while (k >= int_max || (k >= 1 && (hash_set.contains(k)))
                    k = k-1;
                end
                if (k>=1 && !hash_set.contains(k))
                    hash_set.add(k);
                end
                break;
            end
        end
        if (hash_set.size() == int_max):
            break;
        end
    end
        
    for i = 1: (size(temp)(0) / grain)
        hash_set.add(i);
    end

    row = 0;
    iterator = hash_set.iterator;
    while(iterator.hasNext!=0)
        num = iterator.next * grain;
        for i = 0: grain
            for j = 1: size(temp)(1)
                px_red = temp(row)(j)(0);
                px_green = temp(row)(j)(1);
                px_blue = temp(row)(j)(2);

                temp1(num + i)(j)(0) = px_red;
                temp1(num + i)(j)(1) = px_green;
                temp1(num + i)(j)(2) = px_blue;
            end
            row = row+1;
        end
    end

    // column transposition

    len1 = strlength(base64);
    len2 = size(temp)(1);

    if (len2 < len1)
        base64 = substr(base64, 1, len2);
    elseif (len2 > len1):
        s = base64;
        for i = 1:len2/len1
            s = strcat(s,base64);
        end
        base64 = substr(base64, 1, len2);
    end

    hash_set = java.util.HashSet;
    int_max = size(temp)(1) / grain;

    ch = double(base64);
    s = "";
    for i = 1:size(ch)(1)
        s = strcat(s,ch(i));
    end
    ch = s;

    for i = 1:strlen(ch)
        sb1 = "";
        for j = i:strlen(ch)
            sb1 = strcat(sb1,ch(j)); 
            k = str2num(sb1);
            if (k < int_max)
                if (hash_set.contains(k))
                    break;
                else
                    hash_set.add(k);
                end
            else
                while (k >= int_max || (k >= 1 && (hash_set.contains(k)))
                    k = k-1;
                end
                if (k>=1 && !hash_set.contains(k))
                    hash_set.add(k);
                end
                break;
            end
        end
        if (hash_set.size() == int_max):
            break;
        end
    end
        
    for i = 1: (size(temp)(1) / grain)
        hash_set.add(i);
    end

    col = 0;
    iterator = hash_set.iterator;
    while(iterator.hasNext!=0)
        num = iterator.next * grain;
        for i = 0: grain
            for j = 1: size(temp)(0)
                px_red = temp1(j)(col)(0);
                px_green = temp1(j)(col)(1);
                px_blue = temp1(j)(col)(2);

                pic1(j)(num + i)(0) = px_red;
                pic1(j)(num + i)(1) = px_green;
                pic1(j)(num + i)(2) = px_blue;
            end
            col = col+1;
        end
    end

    pic = pic1

end