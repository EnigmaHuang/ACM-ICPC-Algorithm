Const
  MaxPoint = 26;
  MaxEdge  = 60;
  inf      = 'POJ1270.txt';
  ouf      = 'POJ1270ans.txt';
  Ondbg    = true;

Type
  TEdge = record
            target,nextpos:longint;
          end;

Var
  Edges:array[1..MaxEdge]  of TEdge;     //边数组，模拟邻接表
  First:array[1..MaxEdge]  of longint;   //从该顶点出发的边在数组中的最后位置
  InPnt:array[1..MaxPoint] of longint;   //各点的入度数

  Visited:array[1..26] of boolean;
  len,n,EdgesNum:longint;

  ans:string;

Procedure AddEdge(src,trg:longint);
begin
  inc(EdgesNum);
  inc(InPnt[trg]);
  with Edges[EdgesNum] do
  begin
    target:=trg;
    nextpos:=First[src];
  end;
  First[src]:=EdgesNum;
end;

Function ReadData:boolean;
var
  str1,str2:string;
  i,src,trg:longint;
  c1,c2:char;
begin
  Fillchar(First,SizeOf(First),0);
  Fillchar(InPnt,SizeOf(InPnt),0);
  Fillchar(Visited,SizeOf(Visited),true);
  EdgesNum:=0;

  n:=0;

  ReadData:=true;
  if eof(input) then
  begin
    ReadData:=false;
    exit;
  end;

  readln(str1);
  readln(str2);
  for i:=1 to length(str1) do if str1[i]<>' ' then
  begin
    Visited[Ord(str1[i])-Ord('a')+1]:=false;
    inc(n);
  end;

  i:=1;
  while i<=length(str2) do
  begin
    c1:=str2[i];
    c2:=str2[i+2];
    src:=Ord(c1)-Ord('a')+1;
    trg:=Ord(c2)-Ord('a')+1;
    AddEdge(src,trg);
    i:=i+4;
  end;
end;

Procedure TopSort_DFS(depth:longint);
var
  i,j,now,new,nowpos:longint;
begin
  if depth=n+1 then
  begin
    writeln(ans);
    exit;
  end;

  for i:=1 to 26 do if (InPnt[i]=0) and (Visited[i]=false) then  //该点可用
  begin
    now:=i;
    nowpos:=First[now];

    while nowpos<>0 do                  //更新与该点相连的所有点的状态
    begin
      new:=Edges[nowpos].target;
      dec(InPnt[new]);
      nowpos:=Edges[nowpos].nextpos;
    end;
    Visited[now]:=true;                 //更新该点不可用

    ans[depth]:=Chr(Ord('a')-1+i);      //记录当前结果
    TopSort_DFS(depth+1);               //增加深度继续搜索

    nowpos:=First[now];                 //恢复与该点相连的所有点的状态
    while nowpos<>0 do
    begin
      new:=Edges[nowpos].target;
      inc(InPnt[new]);
      nowpos:=Edges[nowpos].nextpos;
    end;
    Visited[now]:=false;                //恢复该点可用
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

  while ReadData=true do
  begin
    ans:='';
    for len:=1 to n do ans:=ans+' ';
    TopSort_DFS(1);
    writeln;
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
