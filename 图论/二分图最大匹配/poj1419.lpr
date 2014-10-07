program poj1419;

Const
  MaxPoint = 100+5;
  inf      = 'poj1419.txt';
  ouf      = 'poj1419ans.txt';
  Ondbg    = true;

Type
  ans=array[1..MaxPoint] of boolean;

Var
  map:array[1..MaxPoint,1..MaxPoint] of boolean;
  best,now:ans;
  bestcnt,nowcnt:integer;
  n,m,testcase:integer;

Procedure DFS(index:integer);
var
  i:integer;
  flag:boolean;
begin
  if index=n+1 then  //所有节点枚举完毕，对比保存搜索结果
  begin
    if nowcnt>bestcnt then
    begin
      bestcnt:=nowcnt;
      best:=now;
    end;
    exit;
  end;

  //检测新加入的点是否到团中的其他节点都存在一条边
  flag:=true;
  for i:=1 to index-1 do if now[i] and map[i,index] then
  begin
    flag:=false;
    break;
  end;

  if flag then  //满足加入条件，记录点并继续搜索
  begin
    now[index]:=true;
    inc(nowcnt);
    DFS(index+1);
    dec(nowcnt);
    now[index]:=false;
  end;
  DFS(index+1);
end;

Procedure ReadData;
var
  i,src,trg:integer;
begin
  fillchar(map,sizeof(map),false);

  readln(n,m);
  for i:=1 to m do
  begin
    readln(src,trg);
    map[src,trg]:=true;
    map[trg,src]:=true;
  end;
end;

Procedure Solve;
var
  i:integer;
begin
  bestcnt:=0;
  nowcnt:=0;
  fillchar(best,sizeof(best),false);
  fillchar(now,sizeof(now),false);

  DFS(1);

  writeln(bestcnt);
  for i:=1 to n do if best[i] then write(i,' ');
  writeln;
end;

Begin
  if Ondbg then
  begin
    Assign(input,inf);
    Reset(input);
    Assign(output,ouf);
    Rewrite(output);
  end;

  readln(testcase);
  while testcase>0 do
  begin
    ReadData;
    Solve;
    dec(testcase);
  end;

  if Ondbg then
  begin
    Close(input);
    Close(output);
  end;
End.

