# 開啟文字檔
x=[]
with open('test.txt', 'r') as file:
    # 讀取並印出檔案內容
    for line in file:
        line=line.strip()
        t="  "
        if line.find(':')!=-1:
            line="//"+line
            t=line
        else:
            line=line.split()
            if len(line)==2:
                t=f"  *e++ = {line[0]}; *e++ = {line[1]};"
            else:
                t=f"  *e++ = {line[0]};"
        x.append(t)

print(x)
with open('test.txt', 'w') as f:
    # 將內容寫入
    for i in x:
        f.write(i+"\n")