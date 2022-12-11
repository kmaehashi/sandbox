#!/usr/bin/env python

# https://trading0.sbisec.co.jp/bff/fbonds/BffBuyOrderList.do?dayNightKbn=1

import sys
import csv
import io


with open(sys.argv[1]) as f:
    data = f.read()

data = data.replace('％\n約定数量', '％\n\n約定数量')

mapping = {
    '残存期間': '残存年数',
    '利率（外貨ベース）': '年率（税引前）',
    '発行体格付': '格付',
    '債券格付': '格付',
}
bonds = []
bond = None
column = None

for line in data.split('\n\n'):
    if line.startswith('\t'):
        if bond is not None:
            bonds.append(bond)
        sub = line.splitlines()
        name = sub[0].split('\t')[1]
        column = sub[1]
        bond = {'銘柄': name}
    elif column is None:
        column = line
    else:
        bond[mapping.get(column, column)] = line
        column = None

if bond is not None:
    bonds.append(bond)


buf = io.StringIO()
w = csv.DictWriter(buf, [
    '銘柄',
    '残存年数',
    '初回コール日',
    '単価',
    '年率（税引前）',
    '利回り（税引前）',
    '申込数量',
    '約定数量',
    '販売単位',
    '利払日',
    '償還日',
    '格付',
    ], dialect='excel-tab')

w.writeheader()
for b in bonds:
    try:
        w.writerow(b)
    except:
        print('errored at:', b)
        raise


print(buf.getvalue())
