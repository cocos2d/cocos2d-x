import os
import MySQLdb
import datetime

def connect_db():
    db_host = os.environ['db_host']
    db_user = os.environ['db_user']
    db_pw = os.environ['db_pw']
    db_name=os.environ['db_name']
    db = MySQLdb.connect(db_host, db_user, db_pw, db_name)
    return db

def close_db(db):
    db.close()

def list_lib_names(db):
    tables=[]
    cursor = db.cursor()
    #sql = "SELECT TABLE_NAME,TABLE_ROWS FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='dailybuild'"
    sql = 'show tables'
    cursor.execute(sql)
    results = cursor.fetchall()
    for row in results:
        tables.append(row[0])
    return tables

def today():
    now = datetime.datetime.now()
    return now.strftime("%Y-%m-%d")

def prev_day(aDay, gap):
    t = datetime.datetime.strptime(aDay, "%Y-%m-%d")
    days = datetime.timedelta(hours=24*gap)
    t = t - days
    return t.strftime("%Y-%m-%d")

def next_day(aDay, gap):
    t = datetime.datetime.strptime(aDay, "%Y-%m-%d")
    days = datetime.timedelta(hours=24*gap)
    t = t + days
    return t.strftime("%Y-%m-%d")

def query_lib_size(db, libname, date):
    cursor = db.cursor()
    t1 = date + ' 00:00:00'
    t2 = next_day(date,1) + ' 00:00:00'
    sql = "SELECT size FROM %s WHERE createdTime > '%s' AND createdTime < '%s'" % (libname, t1, t2)
    cursor.execute(sql)
    result = cursor.fetchone()
    #print libname + ":" + str(result[0])+'kB'
    data = {}
    data[libname] = result[0]
    return data

def query_all_libs(db, date):
    tables = list_lib_names(db)
    result = {}
    for t in tables:
        data = query_lib_size(db, t, date)
        result.update(data)
    return result

db = connect_db()
#print tables
today = today()
Monday = prev_day(today, 4)

csv = "cocos2d-libsize-tracking-"+today+".csv"
with open(csv, "w") as stats_file:
    title = 'date,'
    libs = list_lib_names(db)
    for name in libs:
        title += name
        title += ','
    stats_file.write(title)
    stats_file.write('\n')
    for i in range(0,5):
        d = next_day(Monday, i)
        stats_file.write(d)
        stats_file.write(',')
        stats = query_all_libs(db, d)
        for name in libs:
            size = str(stats[name])
            stats_file.write(size)
            stats_file.write(',')
        stats_file.write('\n')
close_db(db)
#print yesterday