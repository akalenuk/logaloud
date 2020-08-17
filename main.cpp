#include <iostream>

#include <../../src/corelib/io/qfile.h>
#include <../../src/corelib/io/qprocess.h>

// This overwatches some log file as it grows.
// When a new string with error mark substring ("!" by default) appers in it,
// Logaloud prints the string in its own console and then feeds it to Espeak.
//
// Requires Espeak to be installed.
int main(int argc, char* argv[])
{
    if(argc < 2 || argc > 3){
        std::cerr << "Usage: test <filename> [\"<error mark in qoutes>\"]" << std::endl;
        return 1;
    }

    if(!QFile::exists(argv[1])){
        std::cerr << "File " << argv[1] << " not found." << std::endl;
        return 1;
    }

    QString log_name = argv[1];
    QString error_mark = "!";
    if(argc > 2){
        error_mark = argv[2];
    }

    QFile log(log_name);
    qint64 len = log.size();

    QProcess* proc = new QProcess();

    for(;true;){
        qint64 new_len = log.size();
        if(new_len > len){
            log.open(QIODevice::Text | QIODevice::ReadOnly);
            log.seek(len - (len != 0));

            QString line = log.readLine();
            while (!line.isNull() && line != "") {
                if(line.contains(error_mark)){
                    std::cout << line.toAscii().constData();
                    proc->start("espeak", QStringList(line));
                    proc->waitForFinished();
                    proc->close();
                }
                line = log.readLine();
            }
            log.close();
        }
        len = new_len;
        sleep(1);
    }
    return 0;
}
