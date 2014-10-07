Const
  MaxPointNum = 150;
  QueueLength = 200;
  inf='poj1062.txt';
  ouf='poj1062ans.txt';
  OnDebug=false;

//EdgeMap,LinkTo第一二维度和Visited,Dist,Ans 第一维度下标为0，0下标表示人为构造起点
Var
  EdgeMap:array[0..MaxPointNum,0..MaxPointNum] of longint; //存各边之间的权
  LinkTo:array[0..MaxPointNum,0..MaxPointNum] of longint;  //LinkTo[x,y]存与x点相连的第y条边，y=0时为边的总数
  Queue:array[0..QueueLength-1] of longint;                //待松弛队列
  Visited:array[0..MaxPointNum] of boolean;                //是否入队列
  Dist,Relay:array[0..MaxPointNum] of longint;             //到起点的最短路径和中继节点
  head,tail:integer;                                       //队列头尾

  m,n,p,l,x,t,v:integer;
  answer:integer;
  StartLevel,EndLevel:integer;
  level:array[1..MaxPointNum] of longint;                  //主人级别
  relayans:array[0..MaxPointNum] of longint;
  InLevel:array[1..MaxPointNum] of boolean;

Procedure ReadData;
var
  i,j:integer;
begin
  fillchar(EdgeMap,SizeOf(EdgeMap),1);
  fillchar(LinkTo,SizeOf(LinkTo),0);
  fillchar(level,SizeOf(level),0);

  answer:=maxlongint;

  readln(m,n);
  for i:=1 to N do
  begin
    readln(p,l,x);                         //价格，主人等级，替代品数量
    EdgeMap[0,i]:=p;                       //起点直接到该点，即为该物品原价
    level[i]:=l;                           //主人等级
    for j:=1 to x do                       //开始构造边
    begin
      readln(t,v);                         //替代品编号，优惠价格
      EdgeMap[t,i]:=v;                     //可以买了j以后加上优惠价格得到i，故为x指向i
      inc(LinkTo[t,0]);                    //新增边
      LinkTo[t,LinkTo[t,0]]:=i;            //新增边指向i
    end;
  end;

  LinkTo[0,0]:=n;                          //起点可以到任何物品
  for i:=1 to n do LinkTo[0,i]:=i;
end;

Procedure SPFA(start:integer);
var
  i,now,new:integer;
begin
  fillchar(Visited,sizeof(Visited),false);
  fillchar(Dist,SizeOf(Dist),1);
  for i:=1 to n do relay[i]:=i;

  Dist[start]:=0;
  Visited[start]:=true;
  head:=-1;
  tail:=0;
  Queue[tail]:=start;

  while head<>tail do
  begin
    head:=(head+1) mod QueueLength;
    now:=Queue[head];                //队列头出队列进行松弛
    Visited[now]:=false;             //标记出队列

    for i:=1 to LinkTo[now,0] do                                  //穷举所有可用边
    begin
      new:=LinkTo[now,i];
      if (InLevel[new]) and (dist[new]>dist[now]+EdgeMap[now,new]) then   //以当前点为中继点更短
      begin                                                               //更新之
        dist[new]:=dist[now]+EdgeMap[now,new];                            //记录新距离
        relay[new]:=now;                                                  //记录中继节点为当前
        if Visited[new]=false then                                        //新点若未入队
        begin                                                             //入队之
          tail:=(tail+1) mod QueueLength;                                 //加入队尾
          Queue[tail]:=new;
          Visited[new]:=true;                                             //标记已在队列
        end;
      end;
    end;
  end;
end;

Procedure Solve;
var
  i:integer;
begin
  for startlevel:=level[1]-m to level[1] do            //枚举酋长等级允许的区间
  begin
    EndLevel:=StartLevel+m;

    for i:=1 to N do if (level[i]>=StartLevel) and (EndLevel>=level[i])
      then InLevel[i]:=true else InLevel[i]:=false;

    SPFA(0);

    if Dist[1]<answer then
    begin
      answer:=Dist[1];//记录最优解
      for i:=1 to n do relayans[i]:=relay[i];
    end;
  end;
end;

Procedure PrintDebugInfo;
var
  i,j:integer;
begin
  if OnDebug=false then exit;
  i:=1;
  writeln;
  writeln('-----Debug Info Start-----');
  repeat
    write(i,'<-');
    j:=relayans[i];
    write(EdgeMap[j,i],'-');
    i:=j;
  until relayans[i]=i;
end;

Begin
  if OnDebug then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;

  ReadData;
  Solve;
  write(answer);
  PrintDebugInfo;

  Close(input);
  Close(output);
End.

