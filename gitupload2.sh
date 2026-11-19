#!/bin/bash

if [ ! -d ".git" ]; then
    echo "[وضع التهيئة والرفع الأولي للمجلد بالكامل]"
    echo ""
    read -p "https://github.com/mabdelouahab/lasmIDE.git" REPO_URL

    echo ""
    echo "[1/5] جاري تهيئة المستودع المحلي..."
    git init

    echo "[2/5] جاري إضافة جميع الملفات والمجلدات القديمة..."
    git add .

    echo "[3/5] جاري حفظ النسخة الأولى..."
    git commit -m "الرفع الأولي للمجلد بالكامل"

    echo "[4/5] جاري إعداد الفرع الرئيسي والربط..."
    git branch -M main
    git remote add origin "$REPO_URL"

    echo "[5/5] جاري رفع المجلد بالكامل إلى GitHub..."
    git push -u origin main

    echo ""
    echo "=== تم رفع المجلد بنجاح! في المرات القادمة سيتم رفع التحديثات فقط ==="
    exit 0
fi

echo "[وضع التحديثات اليومية]"
echo ""
echo "--- التغييرات الجديدة في المجلد ---"
git status -s
echo "----------------------------------"
echo ""

read -p "أدخل وصف التحديث (اضغط Enter لاستخدام التاريخ والوقت تلقائياً): " COMMIT_MSG
DEFAULT_MSG="تحديث: $(date '+%Y-%m-%d %H:%M')"
COMMIT_MSG=${COMMIT_MSG:-"$DEFAULT_MSG"}

echo ""
echo "[1/4] جاري سحب أي تعديلات من GitHub..."
git pull origin main --rebase

echo "[2/4] جاري إضافة التعديلات الجديدة..."
git add .

echo "[3/4] جاري حفظ التعديلات..."
git commit -m "$COMMIT_MSG"

echo "[4/4] جاري رفع التحديثات إلى GitHub..."
git push origin main

echo ""
echo "=== تمت المزامنة بنجاح! ==="
