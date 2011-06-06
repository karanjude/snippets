def process(k):
    if k <= 0:
        return 0
    val = 1
    q3 = [3]
    q5 = [5]
    q7 = [7]
    
    for i in range(k-1,0,-1):
        val = min(q3[0],q5[0])
        val = min(val,q7[0])
        if val == q7[0]:
            del q7[0]
        else:
            if val == q5[0]:
                del q5[0]
            else:
                del q3[0]
                q3.append(val * 3)
            q5.append(val * 5)
        q7.append(val * 7)
            
    return val

if __name__ == "__main__":
    print process(10)
    
