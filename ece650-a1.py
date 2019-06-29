import re
import sys

dic = {}
StreetAll = []
while(True):
    FullInfo = raw_input()
    FullInfo = FullInfo.lower()
    if re.match(r'^(a|c)\s\"[[a-zA-Z\s]+\"(\s\((0|[1-9][0-9]*|-[1-9][0-9]*)\,(0|[1-9][0-9]*|-[1-9][0-9]*)\))+|g|r\s"[[a-zA-Z\s]+\"',FullInfo):
        if FullInfo == 'g':
           StreetAll = dic.values()
           #print StreetAll
           xcoor = int()
           ycoor = int()


           def intersect(x1, y1, x2, y2, x3, y3, x4, y4):
               global xcoor
               global ycoor
               if (y2 - y1) * (x3 - x4) - (x2 - x1) * (y3 - y4) == 0:
                   return False


               else:
                   xcoor = (
                       (x2 - x1) * (x3 - x4) * (y3 - y1) - x3 * (x2 - x1) * (y3 - y4) + x1 * (y2 - y1) * (
                       x3 - x4)) / ((y2 - y1) * (x3 - x4) - (x2 - x1) * (y3 - y4))
                   ycoor = (
                       (y2 - y1) * (y3 - y4) * (x3 - x1) - y3 * (y2 - y1) * (x3 - x4) + y1 * (x2 - x1) * (
                       y3 - y4)) / ((x2 - x1) * (y3 - y4) - (y2 - y1) * (x3 - x4))

                   if (xcoor - x1) * (xcoor - x2) <= 0 and (xcoor - x3) * (xcoor - x4) <= 0 and (ycoor - y1) * (ycoor - y2) <= 0 and (
                       ycoor - y3) * (ycoor - y4) <= 0:

                       return (xcoor, ycoor)
                   else:
                       return False

           BigVlist = []
           SetBigVlist = []

           Vlist = []
           n = 1
           m = 0
           o = 0
           for i in range(len(StreetAll)):
               for j in range(i + 1, len(StreetAll)):
                   a=0
                   while a < len(StreetAll[i]) - 1:
                       a1 = StreetAll[i][a]
                       a2 = StreetAll[i][a + 1]

                       b = 0
                       while b < len(StreetAll[j]) - 1:
                           b1 = StreetAll[j][b]
                           b2 = StreetAll[j][b + 1]
                           Vlist = intersect(a1[0],a1[1],a2[0],a2[1],b1[0],b1[1],b2[0],b2[1])
                           #print a1,a2,b1,b2
                           if Vlist:
                               BigVlist.append(Vlist)
                               BigVlist.append(a1)
                               BigVlist.append(a2)
                               BigVlist.append(b1)
                               BigVlist.append(b2)

                           b += 1
                       a += 1



                   #print Vlist


           SetBigVlist = {}.fromkeys(BigVlist).keys()
           #print 'SetBigVlist=', SetBigVlist







           SetBigDict = {}

           for u in range(1, len(SetBigVlist) + 1):
               SetBigDict[u] = SetBigVlist[u - 1]

           #print 'V=', SetBigDict
           print 'V = {'
           i = 0

           while i <= len(SetBigDict) - 1:
               print ' ',SetBigDict.keys()[i] , ':'  , SetBigDict.values()[i]
               i = i + 1

           print '}'

           def triangle(x1, x2, y1, y2):
               if x2 - x2 != 0:
                   k = (y1 - y2) / (x1 - x2)
                   return k
               else:
                   return 0


           def invert_dict(d):
               return dict((v, k) for k, v in d.iteritems())


           CStreetAll = invert_dict(SetBigDict)
           # print 'CStreetAll=',CStreetAll




           Tline = []
           a11 = []
           b11 = []
           c = []
           d = []
           Tline = []
           for i in range(len(StreetAll)):
               for j in range(i + 1, len(StreetAll)):
                   a = 0
                   while a < len(StreetAll[i]) - 1:
                       a1 = StreetAll[i][a]
                       a2 = StreetAll[i][a + 1]
                       b = 0
                       while b < len(StreetAll[j]) - 1:
                           b1 = StreetAll[j][b]
                           b2 = StreetAll[j][b + 1]
                           Vlist = intersect(a1[0], a1[1], a2[0], a2[1], b1[0], b1[1], b2[0], b2[1])
                           #print a1, a2, b1, b2
                           if Vlist:
                               t1 = Vlist;
                               t2 = a1;
                               t3 = a2;
                               t4 = b1;
                               t5 = b2;
                               a11 = [t1, t2]
                               b11 = [t1, t3]
                               c = [t1, t4]
                               d = [t1, t5]
                               Tline.append(a11);
                               Tline.append(b11);
                               Tline.append(c);
                               Tline.append(d);

                           b += 1
                       a += 1
           #print 'Tline=',Tline

           m = 0
           i = 0
           for m in range(0, len(Tline) - 3):
               x1 = Tline[m][0][0]
               y1 = Tline[m][0][1]
               x2 = Tline[m][1][0]
               y2 = Tline[m][1][1]
               for i in range(0, len(SetBigVlist)):
                   x = SetBigVlist[i][0]
                   y = SetBigVlist[i][1]
                   if (((y - y2) * (x1 - x2) == (y1 - y2) * (x - x2)) & (min(x1, x2) < x) & (x < max(x1, x2)) & (
                       x1 != x2)) | (
                               ((y - y2) * (x1 - x2) == (y1 - y2) * (x - x2)) & (min(y1, y2) < y) & (y < max(y1, y2)) & (
                       x1 == x2)):
                       del Tline[m]

           #print 'New Tline=',Tline


           UBigVlist = []
           Ulist = []
           XBigVlist = []
           i = 0
           n = 1
           m = 0
           o = 0
           for o in range(0, n + 1):
               while n + 1 <= len(StreetAll):
                   while m + 2 <= len(StreetAll[n]):
                       while i + 2 <= len(StreetAll[o]):
                           Ulist = intersect(StreetAll[o][i][0], StreetAll[o][i][1], StreetAll[o][i + 1][0],
                                             StreetAll[o][i + 1][1], StreetAll[n][m][0], StreetAll[n][m][1],
                                             StreetAll[n][m + 1][0], StreetAll[n][m + 1][1])

                           if Ulist:
                               UBigVlist.append(Ulist);
                               XBigVlist.append(StreetAll[o][i]);
                               XBigVlist.append(StreetAll[o][i + 1]);
                               XBigVlist.append(StreetAll[n][m]);
                               XBigVlist.append(StreetAll[n][m + 1]);
                           i = i + 1
                       m = m + 1
                       i = 0
                   n = n + 1
                   i = 0
                   m = 0
               i = 0
               m = 0


           UBigVlist = [UBigVlist[i] for i in range(len(UBigVlist)) if UBigVlist[i] not in UBigVlist[:i]]

           XBigVlist = [XBigVlist[i] for i in range(len(XBigVlist)) if XBigVlist[i] not in XBigVlist[:i]]

           #print 'U', UBigVlist
           #print 'X', XBigVlist



           u = 0
           r = 0
           t = 0

           Tlist = []
           Deline = []
           for eachStreet in StreetAll:
               i = 0
               while i < len(eachStreet) - 1:
                   x1 = eachStreet[i][0]
                   y1 = eachStreet[i][1]
                   x2 = eachStreet[i + 1][0]
                   y2 = eachStreet[i + 1][1]
                   e = 0
                   for eachIntersection in UBigVlist:
                       x = eachIntersection[0]
                       y = eachIntersection[1]
                       if (((y - y2) * (x1 - x2) == (x - x2) * (y1 - y2)) & (min(x1, x2) < x) & (x < max(x1, x2))) \
                               | (((y - y2) * (x1 - x2) == (x - x2) * (y1 - y2)) & (x1 == x2) & (min(y1, y2) < y) & (
                                   y < max(y1, y2))):
                           Tlist.append(eachIntersection)
                           e = e + 1
                   if e > 1:

                       Tlist.append(eachStreet[i])
                       Tlist.append(eachStreet[i + 1])
                       Deline.append(Tlist)
                       Tlist = []
                   i = i + 1


           #print 'Deline',Deline
           Deline21 = []
           for eachDeline in Deline:
               eachDeline21 = {}.fromkeys(eachDeline).keys()
               Deline21.append(eachDeline21)



           for eachDeline3 in Deline21:
               eachDeline3.sort();

           Deline2 = []

           for each in Deline21:
               c = 1
               while c <= len(each) - 2:
                   Deline2.append(each[c])
                   c = c + 1

           #print Deline2


           edges = []



           for eachTline in Tline:
               A = (CStreetAll[eachTline[0]],CStreetAll[eachTline[1]])
               edges.append(A)


           Edges=[]
           o = 0

           while o + 2 <= len(Deline2):
               B=(CStreetAll[Deline2[o]],CStreetAll[Deline2[o + 1]])
               edges.append(B)
               o = o + 1

           eachedges = {}.fromkeys(edges).keys()

           #print eachedges

           EACHedges=[]

           for x in eachedges:
               if x[0] != x[1]:
                   EACHedges.append(x)
           #print EACHedges



           i = 0


           if len(EACHedges) != 0:
               string=''

               while i <= len(EACHedges) - 2:
                   string +=' <'+str(EACHedges[i][0])+','+str(EACHedges[i][1])+'>,'+'\n'

                   num = 3
                   i= i+1

               string +=' <'+str(EACHedges[i][0])+','+str(EACHedges[i][1])+'>'+'\n}'
               print 'E = {' + '\n'+string
               sys.stdout.flush()
           else:
               print 'E = {' + '\n' +'}'

        else:
            sp = FullInfo.split('"')
            sp[0] = sp[0].strip()
            sp[2] = sp[2].strip()
            if sp[0] == 'a' or sp [0] == 'c':
                sp[2] = sp[2].replace('(', '')
                sp[2] = sp[2].strip().split(')')
                streetPoint = []
                for numPair in sp[2]:
                    if not numPair == '':
                        numPair = numPair.split(',')
                        x = int(numPair[0])
                        y = int(numPair[1])
                        intNumPair = x, y
                        streetPoint.append(intNumPair)
                dic[sp[1]] = streetPoint
    #            print dic
            if sp[0] == 'r':
                sp[2] = sp[2].replace('(', '')
                sp[2] = sp[2].strip().split(')')
                del dic[sp[1]]
    #            print dic

                # the command do not match. You should type the right 'a', 'r', or 'c'
    elif re.match(r'[^arc]\s"[a-zA-Z\s]+"\s\([0-9]+\,[0-9]+\)', FullInfo):
        print 'Error: Sorry, the command do not match. You should type the right a, r, or c.'
    elif re.match(
            r'(a|r|c)"[a-zA-Z\s]+"(\s\([0-9]+\,[0-9]+\))+|(a|r|c)\s"[a-zA-Z\s]+\"\([0-9]+\,[0-9]+\)(\s\([0-9]+\,[0-9]+\))+|(a|r|c)\s"[a-zA-Z\s]+\"\s(\([0-9]+\,[0-9]+\))+|(a|r|c)\"[a-zA-Z\s]+\"(\([0-9]+\,[0-9]+\))+|(a|r|c)\s\"[a-zA-Z\s]+\"(\([0-9]+\,[0-9]+\))+',
            FullInfo):
        print 'Error: Sorry, you are missing spaces in the right position.'
    elif re.match(
            r'(a|r|c)\s[a-zA-Z\s]+\"(\s\([0-9]+\,[0-9]+\))+|(a|r|c)\s\"[a-zA-Z\s]+(\s\([0-9]+\,[0-9]+\))+|(a|r|c)\s[a-zA-Z\s]+(\s\([0-9]+\,[0-9]+\))+',
            FullInfo):
        print 'Error: Sorry, you are missing the double quotation marks.'
    elif re.match(
            r'[a|r|c]\s\"[a-zA-Z\s]+\"(\s[0-9]+\,[0-9]+\))+|[a|r|c]\s\"[a-zA-Z\s]+\"(\s\([0-9]+\,[0-9]+)+|[a|r|c]\s\"[a-zA-Z\s]+\"(\s[0-9]+\,[0-9]+)+',
            FullInfo):
        print 'Error: Sorry, you are missing the brackets.'
    else:

        print 'Error: Sorry, you do not enter right format.'
