var assert = require('assert');
var proc = require('child_process');
var fs = require("fs");

var files = {
    key : 'bin/jeff.key',
    wheel : 'bin/jeff.wheel',
    src : 'bin/jeff.in',
    crypt: 'bin/jeff.crypt',
    decrypt : 'bin/jeff.out'
};

var large = {
    url : 'http://www.textfiles.com/etext/FICTION/quixote',
    file : 'quixote'
}


describe('Self Test',()=>{
    it('self test', function() {
        assert.equal(1, 1);
    });
});


describe('Core Features',()=>{
    it('generates key', (done) => {
        var fname = 'bin/jeff.key';
        var enigma = proc.spawn('bin/enigma.exe', ['\\k', fname]);
        enigma.on('close', (code) => {
            assert.equal(256,fs.statSync(fname).size, 'File exists and is correct size');
            done();
        });
    });
    
    it('generates wheelset',(done)=>{
        var fname = 'bin/jeff.wheel';
        var enigma = proc.spawn('bin/enigma.exe', ['\\w', fname]);
        enigma.on('close', (code) => {
            assert.equal(256*256,fs.statSync(fname).size, 'File exists and is correct size');
            done();
        });
    });
    
    
    it('encrypts file',(done)=>{
        var enigma = proc.spawn('bin/enigma.exe', ['\\e'
            , files.key
            , files.wheel
            , files.src
            , files.encrypt
            ]);
        enigma.on('close', (code) => {
            assert.equal(
                fs.statSync(files.src).size,
                fs.statSync(large.encrypt).size, 
                'File exists and is correct size'
                );
            done();
        });
    });
    
    
    //date +%s; ./enigma.exe /e jeff.key jeff.wheel quixote quixote.crypt; date +%s;
    //136s
    it('decrypts file',(done)=>{
        var enigma = proc.spawn('bin/enigma.exe', ['\\d'
            , files.key
            , files.wheel
            , files.encrypt
            , files.decrypt
            ]);
        enigma.on('close', (code) => {
            assert.equal(
                fs.statSync(files.encrypt).size,
                fs.statSync(large.decrypt).size, 
                'File exists and is correct size'
                );
            assert.equal(
                fs.statSync(files.encrypt).size,
                fs.statSync(large.decrypt).size, 
                'File exists and is correct size'
                );
            done();
        });
    });
    
});


describe('Performance',()=>{
    it('Speed');
});

