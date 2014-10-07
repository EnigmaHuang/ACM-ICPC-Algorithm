Const
  MaxNode=10000;    //顶点数上限

Type
  TEdgePtr = ^TEdge;

  TEdge = record
            s,t:longint;           //边的起始点和终止点
            rev,prev,next:TEdgePtr;//反向边和邻接表中的上一条边，下一条边
          end;

Var
  n,m,bl:longint;                  //顶点数，边数，基图的极大连通子图个数
  g:array[1..MaxNode] of TEdgePtr; //某一个顶点作为出发点的边
  d:array[1..MaxNode] of longint;  //顶点的度
  f:array[1..MaxNode] of longint;  //并查集中元素父结点和启发函数值
  HasEularCyc:boolean;             //原图中是否存在欧拉回路
  link0,link:TEdgePtr;             //用链表保存最终找到的欧拉回路

Procedure AddDirectedEdge(src,trg:longint;var t1,t2:TEdgePtr);
begin
  t1^.s:=src;
  t1^.t:=trg;
  t1^.rev:=t2;
  t1^.prev:=nil;
  t1^.next:=g[src];
  if g[src]<>nil then g[src]^.prev:=t1;
  g[src]:=t1;
end;

Procedure AddEdge(u,v:longint);  //在邻接表中建立边<u,v>
var
  t1,t2:TEdgePtr;
begin
  t1:=new(TEdgePtr);
  t2:=new(TEdgePtr);
  AddDirectedEdge(u,v,t1,t2);
  AddDirectedEdge(v,u,t2,t1);
end;

Function Root(v:longint):Longint;
begin
  if f[v]=v then Root:=v
  else
  begin
    f[v]:=Root(f[v]);
    Root:=f[v];
  end;
end;

Procedure merge(a,b:longint);//在并查集中将a, b两元素合并
var
  fa,fb:longint;
begin
  fa:=Root(a);
  fb:=Root(b);
  if fa<>fb then
  begin
    dec(bl);  //合并后，基图的极大连通子图个数减1
    f[fa]:=fb;
  end;
end;

Procedure init;  //初始化
var
  i,ta,tb:longint;
begin
  fillchar(f,sizeof(f),0);
  fillchar(d,sizeof(d),0);
  readln(n,m);
  for i:=1 to n do f[i]:=i;
  bl:=n;
  for i:=1 to m do
  begin
    readln(ta,tb);
    AddEdge(ta,tb);
    inc(d[tb]);
    inc(d[ta]);
    merge(ta,tb);
  end;
end;

Procedure DelEdge(t:TEdgePtr);//在邻接表中删除边t
var
  no:longint;
begin
  no:=t^.s;
  if t^.prev<>nil then t^.prev^.next:=t^.next
                  else g[no]:=t^.next;
  if t^.next<>nil then t^.next^.prev:=t^.prev;
end;

Procedure FindCyc(src:longint;var head,tail:TEdgePtr);//以src为起点找一条回路，
var                                                   //保存在以head为头，tail为尾的链表中
  i:longint;
begin
  i:=src;
  head:=g[i];  //回路的头部和第一条边
  tail:=head;  //回路的最后一条边=回路的第一条边
  //维护邻接表的完整
  g[i]:=g[i]^.next;
  if g[i]<>nil then g[i]^.prev:=nil;
  //将取出来的边从邻接表中脱离
  tail^.prev:=nil;
  tail^.next:=nil;
  DelEdge(tail^.rev);
  //指向下一个点
  i:=tail^.t;
  while i<>src do    //只要当前点不是出发点
  begin
    tail^.next:=g[i];  //回路中的最后一条边指向当前选定的边
    //维护邻接表的完整
    g[i]:=g[i]^.next;
    if g[i]<>nil then g[i]^.prev:=nil;
    //将取出来的边从邻接表中脱离
    tail:=tail^.next;
    tail^.prev:=nil;
    tail^.next:=nil;
    DelEdge(tail^.rev);
    //指向下一个点
    i:=tail^.t;
  end;
end;

Procedure main;  //主过程
var
  i:longint;
  head,tail:TEdgePtr;
begin
  HasEularCyc:=false;
  for i:=1 to n do if d[i]=0 then dec(bl);  //排除孤立点的影响
  if bl<>1 then exit;                       //原图不连通，无解
  for i:=1 to n do if odd(d[i]) then exit;  //存在奇点，无解

  HasEularCyc:=true;
  for i:=1 to n do
  if d[i]<>0 then break;
  FindCyc(i,head,tail); //首先任意找一条回路
  link:=head;           //当前回路的头部
  link0:=link;          //保存第一个回路的头部
  while link<>nil do if g[link^.t]<>nil then
  begin
    FindCyc(link^.t,head,tail);//找一条新的回路
    tail^.next:=link^.next;    //新回路的尾部指向当前回路的头部，合并回路
    link^.next:=head;          //当前回路的头部为新回路的头部
  end
  else link:=link^.next;
end;

Procedure print;  //输出结果
begin
  if not HasEularCyc then writeln('No solution.')
  else
  begin
    link:=link0;
    writeln(link^.s);
    while link<>nil do
    begin
      writeln(link^.t);
      link:=link^.next;
    end;
  end;
end;

Begin
  init;
  main;
  print;
End.
