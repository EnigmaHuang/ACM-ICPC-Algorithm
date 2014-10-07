Const
  inf='poj1724.txt';
  ouf='poj1724ans.txt';
  MaxPoint=100;
  QueueLen=1005;
  Ondbg=true;

Type
  road=record
         len,cost:longint;
         tgr:longint;
       end;

Var
  Edges:array[1..MaxPoint,1..MaxPoint] of road;
  EdgeNum:array[1..MaxPoint] of longint;
  Queue:array[1..QueueLen] of longint;
  Visited:array[1..MaxPoint] of boolean;
  Dist:array[1..MaxPoint,0..10000] of longint;  //[目的点，可用钱数]

  K,N,R:longint;

Procedure ReadData;
var
  S,D,L,T,i:longint;
begin
  fillchar(Edges,SizeOf(Edges),1);
  fillchar(EdgeNum,SizeOf(EdgeNum),0);

  readln(K);
  readln(N);
  readln(R);
  for i:=1 to R do
  begin
    readln(S,D,L,T);
    inc(EdgeNum[S]);
    Edges[S,EdgeNum[S]].len:=L;
    Edges[S,EdgeNum[S]].tgr:=D;
    Edges[S,EdgeNum[S]].cost:=T;
  end;
end;

Procedure SPFA(start:longint);
var
  head,tail,now,new,i,j:longint;
begin
  fillchar(Dist,SizeOf(Dist),1);
  fillchar(Visited,SizeOf(Visited),false);

  head:=0;
  tail:=1;
  Queue[tail]:=start;
  for i:=0 to 10000 do Dist[1,i]:=0;

  while head<>tail do
  begin
    inc(head);
    if head>QueueLen then head:=head-QueueLen;
    now:=Queue[head];
    Visited[now]:=false;
    for i:=1 to EdgeNum[now] do   //枚举每一条边
    begin
      new:=Edges[Now,i].tgr;
      for j:=Edges[Now,i].cost to K do  //动态规划枚举所有可用的金额
      begin
        if Dist[now,j-Edges[Now,i].cost]+Edges[Now,i].len<Dist[new,j] then
        begin
          Dist[new,j]:=Dist[now,j-Edges[Now,i].cost]+Edges[Now,i].len;
          if Visited[new]=false then
          begin
            inc(tail);
            if tail>QueueLen then tail:=tail-QueueLen;
            Visited[new]:=true;
            Queue[tail]:=new;
          end;
        end;
      end;
    end;
  end;
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;
  ReadData;
  SPFA(1);
  if Dist[N,K]=maxlongint then write('-1') else write(Dist[N,K]);
End.

