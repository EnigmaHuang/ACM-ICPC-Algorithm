Const
  MaxPointNum = 100;
  QueueLength = 200;
  NoDirection = false;  //有向图
  inf='poj1502.txt';
  ouf='poj1502ans.txt';

Var
  EdgeMap:array[1..MaxPointNum,1..MaxPointNum] of longint; //存各边之间的权
  LinkTo:array[1..MaxPointNum,0..MaxPointNum] of longint;  //LinkTo[x,y]存与x点相连的第y条边，y=0时为边的总数
  Queue:array[0..QueueLength-1] of longint;                //待松弛队列
  Visited:array[1..MaxPointNum] of boolean;                //是否入队列
  Dist,Relay:array[1..MaxPointNum] of longint;             //到起点的最短路径，上一个中继点
  ans:array[1..MaxPointNum] of longint;
  head,tail,answer,N:integer;

Function GetParamstr(Cmd:string;index:integer):string;  //分离空格前后各参数  //从以前的代码里copy的
var
  cs:array[1..100] of string;
  i,j:integer;
begin
  for i:=1 to 100 do cs[i]:='';
  i:=1;j:=1;
  while i<=length(cmd) do
  begin
    while (cmd[i]=' ')and(i<=length(cmd)) do inc(i);
    while (cmd[i]<>' ')and(i<=length(cmd)) do
    begin
      cs[j]:=cs[j]+cmd[i];
      inc(i);
    end;
    inc(j);
  end;
  exit(cs[index]);
end;

Procedure ReadData;
var
  c:char;
  tmp,st:string;
  i,j,weight,code:integer;
begin
  readln(N);
  fillchar(LinkTo,SizeOf(LinkTo),0);
  fillchar(EdgeMap,SizeOf(EdgeMap),1);

  EdgeMap[1,1]:=0;
  for i:=2 to N do
  begin
    readln(st);
    for j:=1 to i do
    begin
      tmp:=GetParamstr(st,j); //A STUPID WAY
      if tmp='x' then continue;
      Val(tmp,weight,code);
      EdgeMap[i,j]:=weight;
      EdgeMap[j,i]:=weight;
      weight:=maxlongint;
      inc(LinkTo[i,0]);
      inc(LinkTo[j,0]);
      LinkTo[i,LinkTo[i,0]]:=j;
      LinkTo[j,LinkTo[j,0]]:=i;
    end;
    EdgeMap[i,i]:=0;
  end;
end;

Procedure SPFA(start:integer);
var
  i,j,now:integer;
begin
  fillchar(Visited,sizeof(Visited),false);
  for j:=1 to N do
  begin
    Dist[j]:=MaxLongint;
    Relay[j]:=j;
  end;
  Dist[start]:=0;
  Visited[start]:=true;
  head:=-1;
  tail:=0;
  Queue[tail]:=start;

  while head<>tail do
  begin
    head:=(head+1) mod QueueLength;
    now:=Queue[head];
    Visited[now]:=false;
    for i:=1 to LinkTo[now,0] do
      if dist[LinkTo[now,i]]>dist[now]+EdgeMap[now,LinkTo[now,i]] then
      begin
        dist[LinkTo[now,i]]:=dist[now]+EdgeMap[now,LinkTo[now,i]];
        relay[LinkTo[now,i]]:=now;
        if Visited[LinkTo[now,i]]=false then
        begin
          tail:=(tail+1) mod QueueLength;
          Queue[tail]:=LinkTo[now,i];
          Visited[LinkTo[now,i]]:=true;
        end;
      end;
  end;
end;

Procedure Solve;
var
  i,j,max:Longint;
begin
  SPFA(1);             //妈蛋，信息只可以从第一号CPU传出！源是1不变!
  answer:=0;
  for j:=1 to N do if Dist[j]>answer then answer:=dist[j];
end;

Begin
  Assign(input,inf);
  Reset(input);
  Assign(output,ouf);
  Rewrite(output);

  ReadData;
  Solve;
  write(answer);

  Close(input);
  Close(output);
End.

