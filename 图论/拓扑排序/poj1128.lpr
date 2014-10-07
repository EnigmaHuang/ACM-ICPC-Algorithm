Const
  MaxPoint = 26;
  MaxEdge  = 26*25;
  inf      = 'poj1128.txt';
  ouf      = 'poj1128ans.txt';
  Ondbg    = true;

Type
  TEdge = record
            target,nextpos:integer;
          end;

  TRect = record
            UpX,UpY:integer;     //左上角坐标
            DownX,DownY:integer;     //右下角坐标
          end;

Var
  Edges:array[1..MaxEdge]  of TEdge;     //边数组，模拟邻接表
  First:array[1..MaxEdge]  of integer;   //从该顶点出发的边在数组中的最后位置
  InPnt:array[1..MaxPoint] of integer;   //各点的入度数

  Frames:array[1..MaxPoint] of TRect;    //各框的坐标

  Visited:array[1..26] of boolean;
  n,EdgesNum,len:integer;

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

Procedure UpdatePos(index,x,y:integer);
begin
  with Frames[index] do
  begin
    //如果新的坐标点小于左上角坐标点
    if x<UpX   then UpX:=x;
    if y<UpY   then UpY:=y;
    //如果新的坐标点大于右下角坐标点
    if x>DownX then DownX:=x;
    if y>DownY then DownY:=y;
  end;
end;

Procedure ReadData;
var
  map:array[1..MaxPoint,1..MaxPoint] of char;
  i,j,k:integer;
  h,w,c,id1,id2:integer;
begin
  Fillchar(First,SizeOf(First),0);
  Fillchar(InPnt,SizeOf(InPnt),0);
  Fillchar(Visited,SizeOf(Visited),true);
  fillchar(map,sizeof(map),' ');
  EdgesNum:=0;
  n:=0;

  for i:=1 to MaxPoint do with Frames[i] do  //初始化所有框架记录
  begin
    UpX:=MaxPoint;
    UpY:=MaxPoint;
    DownX:=0;
    DOwny:=0;
  end;

  readln(h);
  readln(w);

  for i:=1 to h do
  begin
    for j:=1 to w do
    begin
      read(map[i,j]);
      if map[i,j]='.' then continue;  //是空点，不处理
      c:=Ord(map[i,j])-Ord('A')+1;
      if Visited[c] then
      begin
        inc(n);                       //统计有多少个字母出现
        Visited[c]:=false;            //标记此字母出现，此字母可用
      end;
      UpdatePos(c,i,j);               //更新位置记录
    end;
    readln;
  end;

  for k:=1 to MaxPoint do if Visited[k]=false then //这个点出现过，构图
  begin
    for i:=Frames[k].UpX to Frames[k].DownX do     //这个框上某一点是其他框的，引一条边
    begin
      id1:=Ord(map[i,Frames[k].UpY])-Ord('A')+1;
      id2:=Ord(map[i,Frames[k].DownY])-Ord('A')+1;
      if id1<>k then AddEdge(k,id1);
      if id2<>k then AddEdge(k,id2);
    end;

    for i:=Frames[k].UpY to Frames[k].DownY do     //这个框上某一点是其他框的，引一条边
    begin
      id1:=Ord(map[Frames[k].UpX,i])-Ord('A')+1;
      id2:=Ord(map[Frames[k].DownX,i])-Ord('A')+1;
      if id1<>k then AddEdge(k,id1);
      if id2<>k then AddEdge(k,id2);
    end;
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

    ans[depth]:=Chr(Ord('A')-1+i);      //记录当前结果
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

  while not eof(input) do
  begin
    ReadData;
    ans:='';
    for len:=1 to n do ans:=ans+' ';
    TopSort_DFS(1);
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.
