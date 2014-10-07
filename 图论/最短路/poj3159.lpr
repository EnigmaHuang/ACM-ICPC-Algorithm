Const
  inf      = 'poj3159.txt';
  ouf      = 'poj3159ans.txt';
  Ondbg    = true;
  StackLen = 70000+20;
  PointNum = 30000+1;
  EdgeNum  = 150000+1;

Type
  TEdge = record
            trg,len:longint;
          end;

Var
  Dist    : array[1..PointNum] of longint;          //Dist[k]表示K比1最多多几个糖果
  Visited : array[1..PointNum] of boolean;          //在栈中的标记
  Stack   : array[1..StackLen] of longint;          //存储的是小朋友的编号

  Edges   : array[1..EdgeNum]  of TEdge;
  First   : array[1..EdgeNum]  of longint;
  Next    : array[1..EdgeNum]  of longint;

  N,M     : longint;
  StackPtr: longint;
  EdgesNum: longint;

Procedure AddEdge(source,target,weight:longint);
begin
  inc(EdgesNum);
  Edges[EdgesNum].trg:=target;
  Edges[EdgesNum].len:=weight;
  //下面模拟链表里后继指向的两句
  Next[EdgesNum]:=First[source]; //Next[k]=n 表示起点为x的边下一条的存储单元在Edges[n],n=0时完毕
  First[source]:=EdgesNum;       //First[x]=k表示起点为x的边第一条的存储单元在Edges[k]
end;

Procedure ReadData;
var
  i:longint;
  A,B,c:longint;
begin
  fillchar(First,SizeOf(First),0);
  fillchar(Next, SizeOf(Next) ,0);
  fillchar(Edges,SizeOf(Edges),1);
  EdgesNum:=0;

  readln(N,M);
  for i:=1 to M do
  begin
    readln(A,B,c);
    AddEdge(A,B,c);           //B比A多，由构图方式决定是A指向B的单向边
  end;
end;

Procedure Push(ID:longint);
begin
  inc(StackPtr);
  Stack[StackPtr]:=ID;
  Visited[ID]:=true;
end;

Function Pop:longint;
begin
  if StackPtr=0 then exit(-1)
  else
  begin
    Visited[Stack[StackPtr]]:=false;
    dec(StackPtr);
    Pop:=Stack[StackPtr+1];
  end;
end;

Function StackEmpty:boolean;
begin
  if StackPtr=0 then StackEmpty:=true
                else StackEmpty:=false;
end;

Procedure SPFA(start:longint);
var
  i,now,new,nowpos: longint;
begin
  fillchar(Dist,SizeOf(Dist),1);
  fillchar(Stack,SizeOf(Stack),0);

  StackPtr:=1;
  Stack[StackPtr]:=start;

  Dist[1]:=0;

  while not StackEmpty() do
  begin
    now:=Pop();
    nowpos:=First[now];
    while nowpos<>0 do
    begin
      new:=Edges[nowpos].trg;
      if Dist[new]>Dist[now]+Edges[nowpos].len then //约束条件是Dist[New]-Dist[now]<=MaxDist(now,new)
      begin
        Dist[new]:=Dist[now]+Edges[nowpos].len;
        if Visited[new]=false then Push(new);
      end;
      nowpos:=Next[nowpos];                         //指向下一条当前点为起点的可用边
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
  write(Dist[N]);
End.